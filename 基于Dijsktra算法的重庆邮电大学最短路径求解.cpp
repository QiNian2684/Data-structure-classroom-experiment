#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <string>
#include <iomanip> // ������ͷ�ļ���ʹ�� std::setw �� std::setfill

using namespace std;

// ����ͼ�Ľṹ��
struct Graph {
    int numVertices;
    vector<vector<int>> adjMatrix;
};

// �ҵ�δ����Ķ����о�����̵Ķ���
int minDistance(const vector<int>& dist, const vector<bool>& sptSet) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < dist.size(); v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// �ݹ麯����ӡ���·��
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

// ʵ��Dijkstra�㷨
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

        // ����յ��Ѿ��ҵ�����ǰ�˳�
        if (u == dest) break;
    }

    cout << "���·������: " << dist[dest] << "��" << endl;
    cout << "���·��: ";
    printPath(parent, dest, buildingNames);
    cout << endl;

    //// ��ӡ���������ƺ���ĸ���ҹ�
    //cout << "���������ƶ��ձ�: ";
    //for (auto const& pair : buildingNames) {
    //    cout << pair.first << "��" << pair.second << " ";
    //}
    //cout << endl;

    // �ܽ����
    cout << buildingNames.at('A' + src) << "��" << buildingNames.at('A' + dest) << "����̾���Ϊ" << dist[dest] << "��" << endl;
}

int main() {
    cout << "����:�����ʵ��ѧ������֮������·�����" << endl;

    // ���ӽ����������·������
    int n = 8; // ���������
    int m = 10; // ·������
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    map<char, string> buildingNames{
        {'A', "����ͼ���"}, {'B', "�ڶ���ѧ¥"}, {'C', "����ʳ��"},
        {'D', "��ͼ���"}, {'E', "�ſƴ�¥"}, {'F', "����Է����"},
        {'G', "������"}, {'H', "ѧ�������"}
    };

    // ���·��
    matrix[0][5] = 100; matrix[0][4] = 30; matrix[0][2] = 10;
    matrix[1][2] = 5; matrix[2][3] = 50; matrix[3][4] = 20;
    matrix[4][5] = 60; matrix[3][5] = 10; matrix[5][6] = 40;
    matrix[6][7] = 70;

    // ȷ�������ǶԳƵ�
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            matrix[j][i] = matrix[i][j];
        }
    }

    // ����ͼʵ��
    Graph g{ n, matrix };

    // ����������ڽӾ���ʹ�ø�ʽ�����
    cout << "�������ڽӾ���:" << endl;
    for (const auto& row : g.adjMatrix) {
        for (int val : row) {
            cout << setw(4) << setfill(' ') << val; // ����ÿ�����ֵĿ��Ϊ4������ĵط��ÿո����
        }
        cout << endl;
    }

    // ���Զ�������յ�
    vector<pair<char, char>> testPoints = { {'A', 'F'}, {'C', 'H'} };

    for (auto& points : testPoints) {
        char start = points.first;
        char end = points.second;
        int startIndex = start - 'A';
        int endIndex = end - 'A';

        cout << "\n\n���� Dijkstra �㷨�� " << buildingNames[start] << " �� " << buildingNames[end] << "..." << endl;
        dijkstra(g, startIndex, endIndex, buildingNames);
    }

    return 0;
}

