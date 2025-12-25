#include "Angel.h"
#include <string>

const glm::vec3 WHITE(1.0, 1.0, 1.0);
const glm::vec3 BLACK(0.0, 0.0, 0.0);
const glm::vec3 RED(1.0, 0.0, 0.0);
const glm::vec3 GREEN(0.0, 0.5, 0.5);
const glm::vec3 BLUE(0.0, 0.0, 1.0);
const glm::vec3 YELLOW(0.76f, 0.70f, 0.50f);

const int TRIANGLE_NUM_POINTS = 3;
const int SQUARE_NUM = 6;
const int SQUARE_NUM_POINTS = 4 * SQUARE_NUM;
const int CIRCLE_NUM_POINTS = 200; // do :circlenumber
const int CIRCLE_NUM_POINTS_2 = 100;
const int CIRCLE_NUM_POINTS_1 = 100;
const int STAR_NUM_POINTS = 100; // do :star

// 每当窗口改变大小，GLFW会调用这个函数并填充相应的参数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

double generateAngleColor(double angle)
{
	return 0.65 / (2 * M_PI) * angle;
}
// 获得三角形的每个角度
double getTriangleAngle(int point)
{
	return 2 * M_PI / 3 * point;
}

// 获得正方形的每个角度
double getSquareAngle(int point)
{
	return M_PI / 4 + (M_PI / 2 * point);
}

// do:get every circle point angle
double getCircleAngle(int point)
{
	return M_PI * 2 * point / CIRCLE_NUM_POINTS_1;
}

// do:获取五角星第 i 个顶点的极坐标角度和半径
void getStarPolar(int point, float &angle, float &radius, float R, float r)
{
	angle = glm::radians(36.0f * point - 90.0f); // 每36°一个点，-90°保证顶点朝上
	radius = (point % 2 == 0) ? R : r;			 // 偶数点在外圈，奇数点在内圈
}

// 生成三角形上的每个点
void generateTrianglePoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	// 三角形尺寸
	glm::vec2 scale(0.8, 0.8);
	// 三角形中心位置
	glm::vec2 center(0, 0);

	// @TODO: Task1 - 在此循环中修改三角形的顶点位置
	for (int i = 0; i < 3; i++)
	{
		// 当前顶点对应的角度
		double currentAngle = getTriangleAngle(i) + M_PI / 2; // 再旋转90度即得
		// 根据角度及三角形中心计算顶点坐标
		vertices[startVertexIndex + i] = glm::vec2(cos(currentAngle), sin(currentAngle)) * scale + center;
	}

	// 确定三个顶点的颜色
	colors[startVertexIndex] = WHITE;
	colors[startVertexIndex + 1] = BLUE;
	colors[startVertexIndex + 2] = GREEN;
}

// 生成正方形上的每个点
void generateSquarePoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	// 最大正方形尺寸
	glm::vec2 scale(1, 0.90);
	// 正方形中心位置
	glm::vec2 center(0.5, -0.25);

	glm::vec3 currentColor = WHITE;
	int vertexIndex = startVertexIndex;

	for (int j = 0; j < 4; j++) // 我就说怎么循环从j开始
	{
		double currentAngle = getSquareAngle(j);
		vertices[vertexIndex] = glm::vec2(sin(currentAngle), cos(currentAngle)) * scale + center;
		colors[vertexIndex] = currentColor;
		vertexIndex++;
	}
}

void generateTrapezoidPoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	glm::vec2 center(-0.2, -0.28);
	glm::vec3 currentColor = YELLOW;
	int vertexIndex = startVertexIndex;

	float scaleXBottom = 0.75f; // 下底宽度
	float scaleXTop = 0.5f;		// 上底宽度
	float scaleY = 0.15f;		// 高度
	vertices[vertexIndex] = glm::vec2(-scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(-scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;

	currentColor = glm::vec3(0.76f, 0.85f, 0.50f);
	center = glm::vec2(-0.2, -0.11);
	scaleXBottom = 0.4f; // 下底宽度
	scaleXTop = 0.25f;	 // 上底宽度
	scaleY = 0.2f;		 // 高度
	vertices[vertexIndex] = glm::vec2(-scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(-scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;

	center = glm::vec2(-0.2, -0.45);
	scaleXBottom = 0.6f; // 下底宽度
	scaleXTop = 0.7f;	 // 上底宽度
	scaleY = 0.2f;		 // 高度
	vertices[vertexIndex] = glm::vec2(-scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(-scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;

	center = glm::vec2(0.4, -0.1);
	scaleXBottom = 0.4f; // 下底宽度
	scaleXTop = 0.4f;	 // 上底宽度
	scaleY = 0.08f;		 // 高度
	vertices[vertexIndex] = glm::vec2(-scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(-scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;

	currentColor = YELLOW;
	center = glm::vec2(-0.2, 0.01);
	scaleXBottom = 0.15f; // 下底宽度
	scaleXTop = 0.1f;	  // 上底宽度
	scaleY = 0.04f;		  // 高度
	vertices[vertexIndex] = glm::vec2(-scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXTop, scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
	vertices[vertexIndex] = glm::vec2(-scaleXBottom, -scaleY / 2.0f) + center;
	colors[vertexIndex++] = currentColor;
}

// do:生成圆形上面的每个点
void generateCirclePoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex, glm::vec2 scale, glm::vec2 center)
{
	// 圆形尺寸

	glm::vec3 currentColor = BLACK;

	int vertexIndex = startVertexIndex;

	for (int i = 0; i < CIRCLE_NUM_POINTS; i++)
	{
		// 当前顶点对应的角度
		double currentAngle = getCircleAngle(i);
		// 根据角度及三角形中心计算顶点坐标
		vertices[vertexIndex] = glm::vec2(cos(currentAngle), sin(currentAngle)) * scale + center;
		colors[vertexIndex] = BLACK;
		vertexIndex++;
	}
}
void generateCirclePoints2(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	// 圆形尺寸
	glm::vec2 scale(0.20, 0.20);
	// 圆形中心位置
	glm::vec2 center(0.60, 0.75);
	glm::vec3 currentColor = BLACK;

	int vertexIndex = startVertexIndex;

	for (int i = 0; i < STAR_NUM_POINTS; i++)
	{
		// 当前顶点对应的角度
		double currentAngle = getCircleAngle(i); // 这样改角度
		// 根据角度及三角形中心计算顶点坐标
		// double currentAngle = M_PI / 4;
		vertices[vertexIndex] = glm::vec2(cos(currentAngle), sin(currentAngle)) * scale + center;
		float t = float(i) / STAR_NUM_POINTS; // 0 ~ 1
		// 颜色从红到黑渐变
		colors[vertexIndex] = glm::mix(glm::vec3(1.0, 0.5, 0.0),
									   glm::vec3(0.0, 0.5, 0.0),
									   t);
		// colors[i] = glm::vec3(generateAngleColor(currentAngle), 0.0, 0.0);
		vertexIndex++;
	}
}
// do: generate star
void generateStarPoints(glm::vec2 vertices[], glm::vec3 colors[], int startVertexIndex)
{
	int numPoints = 10;
	float R = 0.25f; // 外圈半径
	float r = 0.1f;	 // 内圈半径
	glm::vec2 center(-0.70, 0.70);

	int vertexIndex = startVertexIndex;

	for (int i = 0; i < numPoints; i++)
	{
		float angle, radius;
		getStarPolar(i, angle, radius, R, r);

		vertices[vertexIndex] = glm::vec2(cos(angle) * radius,
										  sin(angle) * radius) +
								center;

		// 可以照样用渐变颜色
		float t = (float)i / (numPoints - 1);
		// colors[vertexIndex] = glm::vec3(1.0f - t, 0.0f, t);
		colors[vertexIndex] = GREEN;

		vertexIndex++;
	}
}

// 全局变量，两个vao，一个绘制三角形，一个绘制正方形
GLuint vao[4], program; // todo: the third one used to circle
void init()
{

	// 定义三角形的三个点
	glm::vec2 triangle_vertices[TRIANGLE_NUM_POINTS];
	glm::vec3 triangle_colors[TRIANGLE_NUM_POINTS];
	// 定义矩形的点
	glm::vec2 square_vertices[SQUARE_NUM_POINTS];
	glm::vec3 square_colors[SQUARE_NUM_POINTS];
	// do:define the points of circle
	glm::vec2 circle_vertices[5 * CIRCLE_NUM_POINTS];
	glm::vec3 circle_colors[5 * CIRCLE_NUM_POINTS];
	// do:define the points of circle2
	glm::vec2 star_vertices[STAR_NUM_POINTS];
	glm::vec3 star_colors[STAR_NUM_POINTS];

	// 调用生成形状顶点位置的函数
	glm::vec2 scale(0.1, 0.1);
	// 圆形中心位置
	glm::vec2 center(-0.7, -0.45);
	// do: 绑定圆形的顶点数组对象
	generateTrianglePoints(triangle_vertices, triangle_colors, 0);
	generateTrapezoidPoints(square_vertices, square_colors, 0); // 生成梯形
	for (int i = 0; i < 5; i++)
	{
		glm::vec2 newCenter = center + glm::vec2(i * 0.25f, 0.0f);									   // 生成圆形
		generateCirclePoints(circle_vertices, circle_colors, i * CIRCLE_NUM_POINTS, scale, newCenter); // do define point for circle
	}

	generateCirclePoints2(star_vertices, star_colors, 0); // 太阳

	// 读取着色器并使用
	std::string vshader,
		fshader;
	vshader = "shaders/vshader.glsl";
	fshader = "shaders/fshader.glsl";
	program = InitShader(vshader.c_str(), fshader.c_str());
	glUseProgram(program);

	/*
	 * 初始化三角形的数据
	 */

	// 分配并绑定顶点数组对象
	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);

	// 使用两个顶点缓存对象，分别处理位置和颜色信息
	GLuint vbo[2];

	// 处理三角形位置信息
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	GLuint location = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	// 处理三角形颜色信息
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);
	GLuint cLocation = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));

	/*
	 * 初始化正方形的数据
	 */

	// 分配并绑定顶点数组对象
	glGenVertexArrays(1, &vao[1]);
	glBindVertexArray(vao[1]);

	// 这里不需要额外声明新的vbo，可以重复使用之前声明的vbo变量绑定到不同的vao对象上

	// 处理正方形顶点信息
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
	location = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	// 处理正方形颜色信息
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_colors), square_colors, GL_STATIC_DRAW);
	cLocation = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));

	// 分配并绑定顶点数组对象
	glGenVertexArrays(1, &vao[2]);
	glBindVertexArray(vao[2]);

	// 处理圆形形顶点信息
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_vertices), circle_vertices, GL_STATIC_DRAW);
	location = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	// 处理圆形颜色信息
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle_colors), circle_colors, GL_STATIC_DRAW);
	cLocation = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));

	// 分配并绑定顶点数组对象,
	glGenVertexArrays(1, &vao[3]);
	glBindVertexArray(vao[3]);
	// 处理星形形顶点信息
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(star_vertices), star_vertices, GL_STATIC_DRAW);
	location = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(
		location,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec2),
		BUFFER_OFFSET(0));

	// 处理星形颜色信息
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(star_colors), star_colors, GL_STATIC_DRAW);
	cLocation = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(cLocation);
	glVertexAttribPointer(
		cLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(glm::vec3),
		BUFFER_OFFSET(0));
	// 黑色背景
	glClearColor(0.0, 0.53, 0.81, 0.98);
}

void display(void)
{
	// 清理窗口
	glClear(GL_COLOR_BUFFER_BIT);

	// 激活着色器
	glUseProgram(program);
	// 绑定三角形的顶点数组对象
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, TRIANGLE_NUM_POINTS);

	// 绑定正方形的顶点数组对象
	glBindVertexArray(vao[1]);
	// 注意这里使用的绘制模式为GL_TRIANGLE_FAN
	// 它会以顶点数据的一个点为中心顶点，绘制三角形
	// 绘制多个正方

	for (int i = 0; i < SQUARE_NUM; ++i)
	{
		glDrawArrays(GL_TRIANGLE_FAN, (i * 4), 4);
	}

	glBindVertexArray(vao[2]);
	glLineWidth(10.0f); // 设置线宽为 3 像素
	for (int i = 0; i < 5; i++)
	{
		glDrawArrays(GL_LINE_LOOP, i * CIRCLE_NUM_POINTS, CIRCLE_NUM_POINTS);
	}

	// glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_NUM_POINTS); // 渲染多一个点

	// 绑定星星
	glBindVertexArray(vao[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, STAR_NUM_POINTS);
	//   强制所有进行中的OpenGL命令完成
	glFlush();
}

int main(int argc, char **argv)
{
	// 初始化GLFW库，必须是应用程序调用的第一个GLFW函数
	glfwInit();

	// 配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// 配置窗口属性
	GLFWwindow *window = glfwCreateWindow(1024, 1024, "_坦克是不长后视镜的_", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 调用任何OpenGL的函数之前初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();
	// 在窗口关闭之前循环调用跟绘制有关的函数
	while (!glfwWindowShouldClose(window))
	{
		display();
		// 交换颜色缓冲 以及 检查有没有触发什么事件（比如键盘输入、鼠标移动等）
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
