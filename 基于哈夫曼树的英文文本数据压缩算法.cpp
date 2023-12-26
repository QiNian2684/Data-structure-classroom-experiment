#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

// 哈夫曼树节点
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

// 比较，用于优先队列
struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};

// 打印哈夫曼编码和构建哈夫曼树
void printCodes(struct HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (!root) return;
    if (root->data != '$') {
        huffmanCode[root->data] = str;
    }
    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// 构建哈夫曼树并打印编码
void buildHuffmanTree(string text) {
    // 统计频率
    map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // 创建优先队列，用于构建哈夫曼树
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;

    // 创建叶子节点，并加入到优先队列中
    for (auto pair : freq) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // 构建哈夫曼树
    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    // 打印字符频率
    for (auto pair : freq) {
        cout << pair.first << ":" << pair.second << "  ";
    }
    cout << endl;

    // 生成并打印哈夫曼编码
    map<char, string> huffmanCode;
    printCodes(minHeap.top(), "", huffmanCode);

    cout << "Huffman Codes:" << endl;
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 打印原始字符串和编码后的字符串
    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }
    cout << "Encoded string: " << str << endl;

    // 解码
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
        "aaaaaaabbbbbccdddd", // 示例1
        "aabccc",            // 示例2
        "data compression",  // 示例3
    };

    for (const string& input : inputs) {
        cout << "Processing string: " << input << endl;
        buildHuffmanTree(input);
        cout << endl;
    }
    return 0;
}
