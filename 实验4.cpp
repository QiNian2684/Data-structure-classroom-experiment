#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 无向图类
class UndirectedGraph {
private:
    int numVertices;               // 顶点数量
    vector<vector<int>> adjMatrix; // 邻接矩阵
    void DFSUtil(int v, vector<bool>& visited); // DFS辅助函数

public:
    UndirectedGraph(int numVertices);
    ~UndirectedGraph();
    void addEdge(int i, int j);
    void DFS(int start);
    void BFS(int start);
    void printMatrix();
};

// 有向图类
class DirectedGraph {
private:
    int numVertices;               // 顶点数量
    vector<vector<int>> adjMatrix; // 邻接矩阵
    void DFSUtil(int v, vector<bool>& visited); // DFS辅助函数

public:
    DirectedGraph(int numVertices);
    ~DirectedGraph();
    void addEdge(int i, int j);
    void DFS(int start);
    void BFS(int start);
    void printMatrix();
};

// 无向图的实现

UndirectedGraph::UndirectedGraph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
}

UndirectedGraph::~UndirectedGraph() {
    // 析构函数，可用于释放资源
}

void UndirectedGraph::addEdge(int i, int j) {
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1; // 无向图：添加双向边
}

void UndirectedGraph::DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[v][i] == 1 && !visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

void UndirectedGraph::DFS(int start) {
    vector<bool> visited(numVertices, false);
    DFSUtil(start, visited);
}

void UndirectedGraph::BFS(int start) {
    vector<bool> visited(numVertices, false);
    queue<int> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) {
        int v = queue.front();
        cout << v << " ";
        queue.pop();

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[v][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

void UndirectedGraph::printMatrix() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// 有向图的实现

DirectedGraph::DirectedGraph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
}

DirectedGraph::~DirectedGraph() {
    // 析构函数，可用于释放资源
}

void DirectedGraph::addEdge(int i, int j) {
    adjMatrix[i][j] = 1; // 有向图：添加单向边
}

void DirectedGraph::DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[v][i] == 1 && !visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

void DirectedGraph::DFS(int start) {
    vector<bool> visited(numVertices, false);
    DFSUtil(start, visited);
}

void DirectedGraph::BFS(int start) {
    vector<bool> visited(numVertices, false);
    queue<int> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) {
        int v = queue.front();
        cout << v << " ";
        queue.pop();

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[v][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

void DirectedGraph::printMatrix() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // 创建并操作无向图
    cout << "---- 无向图 ----\n";
    UndirectedGraph ug(5);
    cout << "初始化无向图并添加边...\n";
    ug.addEdge(0, 1);
    ug.addEdge(0, 4);
    ug.addEdge(1, 2);
    ug.addEdge(1, 3);
    ug.addEdge(1, 4);
    ug.addEdge(2, 3);
    ug.addEdge(3, 4);

    cout << "无向图的深度优先遍历（DFS）（从顶点0开始）: ";
    ug.DFS(0);
    cout << "\n无向图的广度优先遍历（BFS）（从顶点0开始）: ";
    ug.BFS(0);
    cout << "\n无向图的邻接矩阵: \n";
    ug.printMatrix();

    // 创建并操作有向图
    cout << "\n---- 有向图 ----\n";
    DirectedGraph dg(5);
    cout << "初始化有向图并添加边...\n";
    dg.addEdge(0, 1);
    dg.addEdge(1, 2);
    dg.addEdge(2, 3);
    dg.addEdge(3, 4);
    dg.addEdge(4, 0);

    cout << "有向图的深度优先遍历（DFS）（从顶点0开始）: ";
    dg.DFS(0);
    cout << "\n有向图的广度优先遍历（BFS）（从顶点0开始）: ";
    dg.BFS(0);
    cout << "\n有向图的邻接矩阵: \n";
    dg.printMatrix();

    return 0;
}
