#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

// ---------- Utility Functions ----------

int getHeight(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

int getBalance(Node* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// ---------- Rotations ----------

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// ---------- Insert with Balancing ----------

Node* insert(Node* node, int key) {
    // 1. Standard BST insert
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // no duplicates
    }

    // 2. Update height
    updateHeight(node);

    // 3. Get balance factor
    int balance = getBalance(node);

    // 4. Handle imbalance cases

    // LL
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ---------- Tree Print (Sideways) ----------

void printTree(Node* root, int space = 0) {
    if (root == nullptr) return;

    space += 6;

    printTree(root->right, space);

    cout << endl;
    for (int i = 6; i < space; i++) {
        cout << " ";
    }

    cout << root->key
         << " (h=" << root->height
         << ", b=" << getBalance(root) << ")" << endl;

    printTree(root->left, space);
}

// ---------- Main ----------

int main() {
    Node* root = nullptr;

    // Example insertions
    int values[] = {30, 20, 10, 25, 40, 50, 22};

    for (int v : values) {
        root = insert(root, v);
    }

    cout << "AVL Tree (sideways):" << endl;
    printTree(root);

    return 0;
}