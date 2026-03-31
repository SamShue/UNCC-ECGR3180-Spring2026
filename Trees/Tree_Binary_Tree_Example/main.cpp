#include <iostream>
#include <string>

struct Node {
    std::string data;
    Node* left;
    Node* right;

    Node(const std::string& val) : data(val), left(nullptr), right(nullptr) {}
};

// Print the tree with indentation to show structure (right → root → left)
void printTree(Node* node, int indent = 0) {
    if (node == nullptr) return;

    printTree(node->right, indent + 4);

    for (int i = 0; i < indent; i++) std::cout << ' ';
    std::cout << node->data << '\n';

    printTree(node->left, indent + 4);
}

int main() {
    //        +
    //       / \
    //      3   *
    //         / \
    //        +   2
    //       / \
    //      5   9

    Node* root                   = new Node("+");
    root->left                   = new Node("3");
    root->right                  = new Node("*");
    root->right->left            = new Node("+");
    root->right->right           = new Node("2");
    root->right->left->left      = new Node("5");
    root->right->left->right     = new Node("9");

    std::cout << "Expression Tree (rotated 90 degrees, root at left):\n\n";
    printTree(root);

    // Clean up
    delete root->right->left->right;
    delete root->right->left->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}
