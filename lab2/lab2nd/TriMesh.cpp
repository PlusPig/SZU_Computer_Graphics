#include "TriMesh.h"

// 一些基础颜色
const glm::vec3 basic_colors[8] = {
    glm::vec3(1.0, 1.0, 1.0), // White
    glm::vec3(0.0, 0.0, 1.0), // Yellow
    glm::vec3(0.0, 0.6, 0.3), // Green
    glm::vec3(0.0, 0.5, 0.7), // Cyan
    glm::vec3(1.0, 0.0, 1.0), // Magenta
    glm::vec3(1.0, 0.0, 0.0), // Red
    glm::vec3(0.0, 0.0, 0.0), // Black
    glm::vec3(0.0, 0.0, 1.0)  // Blue
};

// 立方体的各个点
const glm::vec3 cube_vertices[8] = {
    glm::vec3(-0.5, -0.5, -0.5),
    glm::vec3(0.5, -0.5, -0.5),
    glm::vec3(-0.5, 0.5, -0.5),
    glm::vec3(0.5, 0.5, -0.5),
    glm::vec3(-0.5, -0.5, 0.5),
    glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(-0.5, 0.5, 0.5),
    glm::vec3(0.5, 0.5, 0.5)};

TriMesh::TriMesh()
{
}

TriMesh::~TriMesh()
{
}

std::vector<glm::vec3> TriMesh::getVertexPositions()
{
    return vertex_positions;
}

std::vector<glm::vec3> TriMesh::getVertexColors()
{
    return vertex_colors;
}

std::vector<vec3i> TriMesh::getFaces()
{
    return faces;
}

std::vector<glm::vec3> TriMesh::getPoints()
{
    return points;
}

std::vector<glm::vec3> TriMesh::getColors()
{
    return colors;
}

void TriMesh::cleanData()
{
    vertex_positions.clear();
    vertex_colors.clear();

    faces.clear();

    points.clear();
    colors.clear();
}

void TriMesh::storeFacesPoints()
{

    // @TODO: Task-2修改此函数在points和colors容器中存储每个三角面片的各个点和颜色信息
    // 根据每个三角面片的顶点下标存储要传入GPU的数据
    // 记录点的位置
    for (int j = 0; j < faces.size(); j++)
    {
        unsigned int idx[3] = {faces[j].x, faces[j].y, faces[j].z};
        for (int i = 0; i < 3; i++)
        {
            points.push_back(vertex_positions[idx[i]]);
            colors.push_back(vertex_colors[j % 4]);
            // 这里颜色可能可以自己写
        }
    }
}

// 立方体生成12个三角形的顶点索引
void TriMesh::generateCube()
{
    // 创建顶点前要先把那些vector清空
    cleanData();

    // @TODO: Task1-修改此函数，存储立方体的各个面信息
    //  vertex_positions和vertex_colors先保存每个顶点的数据
    for (int i = 0; i < 8; i++)
    {
        vertex_positions.push_back(cube_vertices[i]);
        vertex_colors.push_back(basic_colors[i % 8]);
    }
    //  faces再记录每个面片上顶点的下标
    // 全部按逆时针排序
    faces.clear();
    faces = {
        // 前面
        {0, 1, 3},
        {0, 3, 2},
        // 后面
        {4, 7, 5},
        {4, 6, 7},
        // 左面
        {0, 4, 5},
        {0, 5, 1},
        // 右面
        {2, 7, 3},
        {2, 6, 7},
        // 底面
        {0, 2, 6},
        {0, 6, 4},
        // 顶面
        {1, 7, 5},
        {1, 3, 7}};

    storeFacesPoints();
}
// 上面是自己写的，调用自己的顶点和颜色，下面则是读文件写法
void TriMesh::readOff(const std::string &filename)
{
    // fin打开文件读取文件信息
    if (filename.empty())
    {
        return;
    }
    std::ifstream fin;
    fin.open(filename);
    if (!fin)
    {
        printf("File on error\n");
        return;
    }
    else
    {
        printf("File open success\n");
        cleanData();
        int nVertices, nFaces, nEdges;

        // 读取OFF字符串
        std::string str;
        fin >> str;
        // 读取文件中顶点数、面片数、边数
        fin >> nVertices >> nFaces >> nEdges;
        // 根据顶点数，循环读取每个顶点坐标
        for (int i = 0; i < nVertices; i++)
        {
            glm::vec3 tmp_node;
            fin >> tmp_node.x >> tmp_node.y >> tmp_node.z;
            vertex_positions.push_back(tmp_node);
            vertex_colors.push_back(basic_colors[i % 5]);
        }
        // 上面是记录每个点的数据，后面是记录每个点的属性，叫我们弄的是把点按顺序放好
        //  根据面片数，循环读取每个面片信息，并用构建的vec3i结构体保存
        for (int i = 0; i < nFaces; i++)
        {
            int num, a, b, c;
            // num记录此面片由几个顶点构成，a、b、c为构成该面片顶点序号
            fin >> num >> a >> b >> c;
            faces.push_back(vec3i(a, b, c));
        }
    }
    fin.close();
    storeFacesPoints();
};