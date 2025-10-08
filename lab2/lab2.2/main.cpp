#include "Angel.h"

#include <vector>
#include <fstream>
#include <string>

using namespace std;

int window;
// ������Ƭ�еĶ�������
typedef struct vIndex
{
	unsigned int a, b, c;
	vIndex(int ia, int ib, int ic) : a(ia), b(ib), c(ic) {}
} vec3i;

std::vector<glm::vec3> vertices;
std::vector<vec3i> faces;

int nVertices = 0;
int nFaces = 0;
int nEdges = 0;

std::vector<glm::vec3> points; // ������ɫ���Ļ��Ƶ�
std::vector<glm::vec3> colors; // ������ɫ������ɫ

const int NUM_VERTICES = 8;

const glm::vec3 vertex_colors[NUM_VERTICES] = {
	glm::vec3(1.0, 1.0, 1.0), // White
	glm::vec3(1.0, 1.0, 0.0), // Yellow
	glm::vec3(0.0, 1.0, 0.0), // Green
	glm::vec3(0.0, 1.0, 1.0), // Cyan
	glm::vec3(1.0, 0.0, 1.0), // Magenta
	glm::vec3(1.0, 0.0, 0.0), // Red
	glm::vec3(0.0, 0.0, 0.0), // Black
	glm::vec3(0.0, 0.0, 1.0)  // Blue
};

void read_off(const std::string filename)
{
	// fin���ļ���ȡ�ļ���Ϣ
	if (filename.empty())
	{
		return;
	}
	std::ifstream fin;
	fin.open(filename);
	// @TODO: Task1:�޸Ĵ˺�����ȡOFF�ļ�����άģ�͵���Ϣ
	if (!fin)
	{
		printf("�ļ�����\n");
		return;
	}
	else
	{
		printf("�ļ��򿪳ɹ�\n");
		vertices.clear();
		faces.clear();

		// ��ȡOFF�ַ���
		string str;
		fin >> str;
		// ��ȡ�ļ��ж���������Ƭ��������
		fin >> nVertices >> nFaces >> nEdges;

		// ���ݶ�������ѭ����ȡÿ���������꣬���䱣�浽vertices
		for (int i = 0; i < nVertices; i++)
		{
			double x, y, z;
			fin >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
			// û�з����ڴ棬������Ҫpushback
		}
		// ������Ƭ����ѭ����ȡÿ����Ƭ��Ϣ�����ù�����vec3i�ṹ�屣�浽faces
		for (int i = 0; i < nFaces; i++)
		{
			int num, a, b, c;
			fin >> num >> a >> b >> c;
			faces.push_back({a, b, c});
		}
	}
	fin.close();
}

void storeFacesPoints()
{
	points.clear();
	colors.clear();
	// @TODO: Task1:�޸Ĵ˺�����points��colors�����д洢ÿ��������Ƭ�ĸ��������ɫ��Ϣ
	// ��points�����У��������ÿ����Ƭ�Ķ��㣬����colors�����У���Ӹõ����ɫ��Ϣ
	// ����һ�������������������ι��ɣ���ôvertices����4����������ݹ��ɣ�faces���¼���������εĶ����±꣬
	// ��points���Ǽ�¼��2�������εĶ��㣬�ܹ�6����������ݡ�
	for (int i = 0; i < faces.size(); i++)
	{
		unsigned int idx[3] = {faces[i].a, faces[i].b, faces[i].c};
		// �ֱ��ʾ3����ͬ�ĵ㣬Ȼ��ȥvertex�������ҳ�������Ϊ��¼�����±�
		for (int j = 0; j < 3; j++)
		{
			glm::vec3 v = vertices[idx[j]];
			points.push_back(v); // ��ʾ����˳��
			glm::vec3 color = vertex_colors[idx[j] % 8];
			colors.push_back(color);
		}
	}
	// colors�������Ǻ�points�Ķ���һһ��Ӧ����������������ɫ���������ǿ���ʹ�ö�����������Լ��趨����ɫ��ֵ��
}

void init()
{
	// ��ȡoffģ���ļ�
	read_off("./assets/cube.off");
	storeFacesPoints();

	// ���������������
	GLuint vao[1];
	glGenVertexArrays(1, vao); // ����1�������������
	glBindVertexArray(vao[0]); // �󶨶����������

	// ��������ʼ�����㻺�����
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3) + colors.size() * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);

	// @TODO: Task1:�޸���ɺ��ٴ�����ע�ͣ��������ᱨ��
	// �ֱ��ȡ����
	glBufferSubData(GL_ARRAY_BUFFER, 0, points.size() * sizeof(glm::vec3), &points[0]);
	glBufferSubData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), colors.size() * sizeof(glm::vec3), &colors[0]);

	// ��ȡ��ɫ����ʹ��
	std::string vshader, fshader;
	vshader = "shaders/vshader.glsl";
	fshader = "shaders/fshader.glsl";
	GLuint program = InitShader(vshader.c_str(), fshader.c_str());
	glUseProgram(program);

	// �Ӷ�����ɫ���г�ʼ�������λ��
	GLuint pLocation = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(pLocation);
	glVertexAttribPointer(pLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	// �Ӷ�����ɫ���г�ʼ���������ɫ
	GLuint cLocation = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(cLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(points.size() * sizeof(glm::vec3)));

	// ��ɫ����
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
	// @TODO: Task2:�����ڣ�������ɫ�������Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, points.size());
}

// ���ڼ��̻ص�������
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	// ���ŵ��ڴ��ļ�һ��=�ű�ʾ���ļ���
	else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	{
		cout << "read cube.off" << endl;
		read_off("./assets/cube.off");
		storeFacesPoints();
		// @TODO: Task1:�޸���ɺ��ٴ�����ע�ͣ��������ᱨ��
		glBufferSubData(GL_ARRAY_BUFFER, 0, points.size() * sizeof(glm::vec3), &points[0]);
		glBufferSubData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), colors.size() * sizeof(glm::vec3), &colors[0]);
	}
	else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	{
		cout << "read cube2.off" << endl;
		read_off("./assets/cube2.off");
		storeFacesPoints();
		// @TODO: Task1:�޸���ɺ��ٴ�����ע�ͣ��������ᱨ��
		glBufferSubData(GL_ARRAY_BUFFER, 0, points.size() * sizeof(glm::vec3), &points[0]);
		glBufferSubData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), colors.size() * sizeof(glm::vec3), &colors[0]);
	}
	else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		cout << "reset" << endl;
		// �ر���Ȳ���
		glDisable(GL_DEPTH_TEST);
		// �ر����޳�
		glDisable(GL_CULL_FACE);
		// ʹ��������ģʽ
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	// @TODO: Task2:������Ȳ���
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mode == 0x0000) // 0x0000��ʾ��ϼ�Ϊ��
	{
		glEnable(GL_DEPTH_TEST);
		cout << "depth test: enable" << endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	// @TODO: Task2:�ر���Ȳ���
	else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		glDisable(GL_DEPTH_TEST);
		cout << "depth test: disable" << endl;
	}
	// @TODO: Task3:���÷����޳�
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mode == 0x0000)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		cout << "cull back: enable" << endl;
	}
	// @TODO: Task3:�رշ����޳�
	else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		glDisable(GL_CULL_FACE);
		cout << "cull back: disable" << endl;
	}
	// @TODO: Task4:���������޳�
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mode == 0x0000)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		cout << "cull front: enable" << endl;
	}
	// @TODO: Task4:�ر������޳�
	else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		glDisable(GL_CULL_FACE);
		cout << "cull front: disable" << endl;
	}
	// @TODO: Task5:�����߻���ģʽ
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS && mode == 0x0000)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		cout << "line mode: enable" << endl;
	}
	// @TODO: Task5:�ر��߻���ģʽ
	else if (key == GLFW_KEY_4 && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		cout << "line mode: disable" << endl;
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char **argv)
{
	// ��ʼ��GLFW�⣬������Ӧ�ó�����õĵ�һ��GLFW����
	glfwInit();

	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// ���ô�������
	GLFWwindow *window = glfwCreateWindow(600, 600, "2023152019_lab2.2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// �����κ�OpenGL�ĺ���֮ǰ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();
	while (!glfwWindowShouldClose(window))
	{
		display();

		// ������ɫ���� �Լ� �����û�д���ʲô�¼�������������롢����ƶ��ȣ�
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}