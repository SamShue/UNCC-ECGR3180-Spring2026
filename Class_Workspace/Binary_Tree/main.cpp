#include <iostream>

using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;

    Node(const string& data){
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

void printTree(Node* node, int indent = 0){
    if(node == nullptr) return;

    printTree(node->right, indent + 4);

    for(int i = 0; i < indent; i++)
        cout << ' ';

    cout << node->data << endl;

    printTree(node->left, indent + 4);
}

int evaluate(Node* root){
    if(root->left == nullptr && root->right == nullptr){
        return stoi(root->data);
    }

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    if(root->data == "+") return leftVal + rightVal;
    if(root->data == "-") return leftVal - rightVal;
    if(root->data == "*") return leftVal * rightVal;
    if(root->data == "/") return leftVal / rightVal;

    // Should not get here
    return 0;
}

int main() {
    // level 0
    Node* root = new Node("+");
    // level 1
    root->left = new Node("3");
    root->right = new Node("*");
    // level 2
    root->right->left = new Node("+");
    root->right->right = new Node("2");
    // level 3
    root->right->left->left = new Node("5");
    root->right->left->right = new Node("9");

    printTree(root);

    cout << "Result of equation: " << evaluate(root) << endl;
    
    return 0;
}