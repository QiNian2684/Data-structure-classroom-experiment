#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <string>
#include <iomanip> // 添加这个头文件来使用 std::setw 和 std::setfill

using namespace std;

// 定义图的结构体
struct Graph {
    int numVertices;
    vector<vector<int>> adjMatrix;
};

// 找到未处理的顶点中距离最短的顶点
int minDistance(const vector<int>& dist, const vector<bool>& sptSet) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < dist.size(); v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// 递归函数打印最短路径
void printPath(const vector<int>& parent, int j, const map<char, string>& buildingNames) {
    // Find the letter corresponding to the current node
    char node = 'A' + j;
    if (parent[j] == -1) {
        cout << buildingNames.at(node);
        return;
    }
    printPath(parent, parent[j], buildingNames);
    cout << " ---> " << buildingNames.at(node);
}

// 实现Dijkstra算法
void dijkstra(const Graph& graph, int src, int dest, const map<char, string>& buildingNames) {
    vector<int> dist(graph.numVertices, INT_MAX);
    vector<bool> sptSet(graph.numVertices, false);
    vector<int> parent(graph.numVertices, -1);

    dist[src] = 0;

    for (int count = 0; count < graph.numVertices - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < graph.numVertices; v++) {
            if (!sptSet[v] && graph.adjMatrix[u][v] && dist[u] + graph.adjMatrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph.adjMatrix[u][v];
            }
        }

        // 如果终点已经找到，提前退出
        if (u == dest) break;
    }

    cout << "最短路径长度: " << dist[dest] << "米" << endl;
    cout << "最短路径: ";
    printPath(parent, dest, buildingNames);
    cout << endl;

    //// 打印建筑物名称和字母名挂钩
    //cout << "建筑物名称对照表: ";
    //for (auto const& pair : buildingNames) {
    //    cout << pair.first << "：" << pair.second << " ";
    //}
    //cout << endl;

    // 总结输出
    cout << buildingNames.at('A' + src) << "到" << buildingNames.at('A' + dest) << "的最短距离为" << dist[dest] << "米" << endl;
}

int main() {
    cout << "案例:重庆邮电大学建筑物之间的最短路径求解" << endl;

    // 增加建筑物个数和路径条数
    int n = 8; // 建筑物个数
    int m = 10; // 路径条数
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    map<char, string> buildingNames{
        {'A', "数字图书馆"}, {'B', "第二教学楼"}, {'C', "中心食堂"},
        {'D', "老图书馆"}, {'E', "信科大楼"}, {'F', "宁静苑二舍"},
        {'G', "体育馆"}, {'H', "学生活动中心"}
    };

    // 添加路径
    matrix[0][5] = 100; matrix[0][4] = 30; matrix[0][2] = 10;
    matrix[1][2] = 5; matrix[2][3] = 50; matrix[3][4] = 20;
    matrix[4][5] = 60; matrix[3][5] = 10; matrix[5][6] = 40;
    matrix[6][7] = 70;

    // 确保矩阵是对称的
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            matrix[j][i] = matrix[i][j];
        }
    }

    // 创建图实例
    Graph g{ n, matrix };

    // 输出构建的邻接矩阵，使用格式化输出
    cout << "构建的邻接矩阵:" << endl;
    for (const auto& row : g.adjMatrix) {
        for (int val : row) {
            cout << setw(4) << setfill(' ') << val; // 设置每个数字的宽度为4，不足的地方用空格填充
        }
        cout << endl;
    }

    // 测试多对起点和终点
    vector<pair<char, char>> testPoints = { {'A', 'F'}, {'C', 'H'} };

    for (auto& points : testPoints) {
        char start = points.first;
        char end = points.second;
        int startIndex = start - 'A';
        int endIndex = end - 'A';

        cout << "\n\n运行 Dijkstra 算法从 " << buildingNames[start] << " 到 " << buildingNames[end] << "..." << endl;
        dijkstra(g, startIndex, endIndex, buildingNames);
    }

    return 0;
}

