#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class AVLTree {
private:
    struct Node {
        string key;
        int value;
        Node* left;
        Node* right;
        int height;

        Node(string key, int value) : key(key), value(value), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root;

    // ---------- Utility ----------

    int getHeight(Node* node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    void updateHeight(Node* node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // ---------- Rotations ----------

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // ---------- Insert ----------

    Node* insert(Node* node, string key, int value) {
        if (node == nullptr)
            return new Node(key, value);

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            return node; // duplicate key, do nothing
        }

        updateHeight(node);

        int balance = getBalance(node);

        // LL case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // LR case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // RL case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // ---------- Search ----------

    Node* search(Node* node, string key) {
        if (node == nullptr)
            return nullptr;

        if (key == node->key)
            return node;
        else if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // ---------- Print ----------

    void printTree(Node* node, int space = 0) {
        if (node == nullptr) return;

        space += 6;

        printTree(node->right, space);

        cout << endl;
        for (int i = 0; i < space; i++)
            cout << " ";
        cout << node->key << " (H: " << node->height << ")" << endl;

        printTree(node->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string key, int value) {
        root = insert(root, key, value);
    }

    // Returns true if the key exists in the tree.
    bool find(string key) {
        return search(root, key) != nullptr;
    }

    // Returns the value for the given key, or -1 if not found.
    int get(string key) {
        Node* node = search(root, key);
        if (node == nullptr)
            return -1;
        return node->value;
    }

    // Updates the value for an existing key. Does nothing if not found.
    void set(string key, int value) {
        Node* node = search(root, key);
        if (node != nullptr)
            node->value = value;
    }

    void increment(string key) {
        Node* node = search(root, key);
        if (node != nullptr)
            node->value++;
    }

    void print() {
        printTree(root);
    }
};

/*
vector<pair<string, int>> dictornay;

int find(string key){
    for (int i = 0; i < dictornay.size(); i++){
        if(dictornay[i].first == key){
            return i;
        }
    }
    return -1;
}
*/

AVLTree dictionary;

string toLower(string word) {
    for (char& c : word)
        c = tolower(c);
    return word;
}

int main() {
    ifstream file("olivertwist.txt");
    if (!file.is_open()) {
        cout << "Error: could not open file" << endl;
        return 1;
    }

    string word;
    while (file >> word) {
        word = toLower(word);

        if(dictionary.find(word)){
            dictionary.increment(word);
        } else {
            dictionary.insert(word, 1);
        }

    }

    cout << "Frequency of the word \"the\": " << dictionary.get("the") << endl;

    /*
    string word;
    while (file >> word) {
        word = toLower(word);

        int index = find(word);
        if(index >= 0){
            dictornay[index].second++;
        } else {
            dictornay.push_back(pair<string, int>(word, 1));
        }

    }

    for(int i = 0; i < dictornay.size(); i++){
        cout << dictornay[i].first << ": " << dictornay[i].second << endl;
    }
    */
    file.close();

    return 0;
}
