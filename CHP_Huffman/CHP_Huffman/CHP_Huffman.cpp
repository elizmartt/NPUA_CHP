#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(char s, int f) : symbol(s), frequency(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

void generateCodes(Node* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->symbol] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

void huffmanEncoding(const string& input) {
    unordered_map<char, int> frequencyMap;
    for (char ch : input) {
        frequencyMap[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : frequencyMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sumNode = new Node('\0', left->frequency + right->frequency);
        sumNode->left = left;
        sumNode->right = right;

        pq.push(sumNode);
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    cout << "\nEncoded String:\n";
    string encodedString;
    for (char ch : input) {
        encodedString += huffmanCodes[ch];
    }
    cout << encodedString << "\n";

}

int main() {
    cout << "Enter a string: ";
    string input;
    getline(cin, input);

    huffmanEncoding(input);

    return 0;
}
