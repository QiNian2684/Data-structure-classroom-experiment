#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

// ���������ڵ�
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode* left, * right;

    HuffmanNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// �Ƚϣ��������ȶ���
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};

// ��ӡ����������͹�����������
void printCodes(struct HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (!root) return;
    if (root->data != '$') {
        huffmanCode[root->data] = str;
    }
    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// ����������������ӡ����
void buildHuffmanTree(string text) {
    // ͳ��Ƶ��
    map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // �������ȶ��У����ڹ�����������
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;

    // ����Ҷ�ӽڵ㣬�����뵽���ȶ�����
    for (auto pair : freq) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // ������������
    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    // ��ӡ�ַ�Ƶ��
    for (auto pair : freq) {
        cout << pair.first << ":" << pair.second << "  ";
    }
    cout << endl;

    // ���ɲ���ӡ����������
    map<char, string> huffmanCode;
    printCodes(minHeap.top(), "", huffmanCode);

    cout << "Huffman Codes:" << endl;
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // ��ӡԭʼ�ַ����ͱ������ַ���
    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }
    cout << "Encoded string: " << str << endl;

    // ����
    string decodedString = "";
    HuffmanNode* curr = minHeap.top();
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '0') curr = curr->left;
        else curr = curr->right;

        if (curr->left == nullptr && curr->right == nullptr) {
            decodedString += curr->data;
            curr = minHeap.top();
        }
    }
    cout << "Decoded string: " << decodedString << endl;
}

int main() {
    vector<string> inputs = {
        "aaaaaaabbbbbccdddd", // ʾ��1
        "aabccc",            // ʾ��2
        "data compression",  // ʾ��3
    };

    for (const string& input : inputs) {
        cout << "Processing string: " << input << endl;
        buildHuffmanTree(input);
        cout << endl;
    }
    return 0;
}
