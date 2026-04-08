#include <iostream>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value){
        key = value;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

int getHeight(Node* node){
    if(node == nullptr)
        return -1;
    
    return node->height;
}

void updateHeight(Node* node){
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

int getBalance(Node* node){
    if(node == nullptr)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

void printTree(Node* root, int space = 0){
    if (root == nullptr) return;

    space += 6;

    printTree(root->right, space);

    cout << endl;
    for(int i = 0; i < space; i++){
        cout << " ";
    }

    cout << root->key << "(H: " << root->height << ")" << endl;

    printTree(root->left, space);
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

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* insert(Node* node, int key){
    if(node == nullptr){
        return new Node(key);
    }

    if(key < node->key){
        node->left = insert(node->left, key);
    } else if(key > node->key){
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);

    // LL case
    if(balance > 1 && key < node->left->key){
        return rightRotate(node);
    }

    // LR case
    if(balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 10);
    root = insert(root, 11);

    printTree(root);

    return 0;
}