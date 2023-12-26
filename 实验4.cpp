#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ����ͼ��
class UndirectedGraph {
private:
    int numVertices;               // ��������
    vector<vector<int>> adjMatrix; // �ڽӾ���
    void DFSUtil(int v, vector<bool>& visited); // DFS��������

public:
    UndirectedGraph(int numVertices);
    ~UndirectedGraph();
    void addEdge(int i, int j);
    void DFS(int start);
    void BFS(int start);
    void printMatrix();
};

// ����ͼ��
class DirectedGraph {
private:
    int numVertices;               // ��������
    vector<vector<int>> adjMatrix; // �ڽӾ���
    void DFSUtil(int v, vector<bool>& visited); // DFS��������

public:
    DirectedGraph(int numVertices);
    ~DirectedGraph();
    void addEdge(int i, int j);
    void DFS(int start);
    void BFS(int start);
    void printMatrix();
};

// ����ͼ��ʵ��

UndirectedGraph::UndirectedGraph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
}

UndirectedGraph::~UndirectedGraph() {
    // �����������������ͷ���Դ
}

void UndirectedGraph::addEdge(int i, int j) {
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1; // ����ͼ�����˫���
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

// ����ͼ��ʵ��

DirectedGraph::DirectedGraph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
}

DirectedGraph::~DirectedGraph() {
    // �����������������ͷ���Դ
}

void DirectedGraph::addEdge(int i, int j) {
    adjMatrix[i][j] = 1; // ����ͼ����ӵ����
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
    // ��������������ͼ
    cout << "---- ����ͼ ----\n";
    UndirectedGraph ug(5);
    cout << "��ʼ������ͼ����ӱ�...\n";
    ug.addEdge(0, 1);
    ug.addEdge(0, 4);
    ug.addEdge(1, 2);
    ug.addEdge(1, 3);
    ug.addEdge(1, 4);
    ug.addEdge(2, 3);
    ug.addEdge(3, 4);

    cout << "����ͼ��������ȱ�����DFS�����Ӷ���0��ʼ��: ";
    ug.DFS(0);
    cout << "\n����ͼ�Ĺ�����ȱ�����BFS�����Ӷ���0��ʼ��: ";
    ug.BFS(0);
    cout << "\n����ͼ���ڽӾ���: \n";
    ug.printMatrix();

    // ��������������ͼ
    cout << "\n---- ����ͼ ----\n";
    DirectedGraph dg(5);
    cout << "��ʼ������ͼ����ӱ�...\n";
    dg.addEdge(0, 1);
    dg.addEdge(1, 2);
    dg.addEdge(2, 3);
    dg.addEdge(3, 4);
    dg.addEdge(4, 0);

    cout << "����ͼ��������ȱ�����DFS�����Ӷ���0��ʼ��: ";
    dg.DFS(0);
    cout << "\n����ͼ�Ĺ�����ȱ�����BFS�����Ӷ���0��ʼ��: ";
    dg.BFS(0);
    cout << "\n����ͼ���ڽӾ���: \n";
    dg.printMatrix();

    return 0;
}
