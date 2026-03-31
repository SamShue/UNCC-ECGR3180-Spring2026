#include <iostream>
#include <vector>
using namespace std;

struct Node {
    string name;
    vector<Node*> children;

    Node(string n) : name(n) {}
};

// Print tree (recursive traversal)
void printTree(Node* node, int depth = 0) {
    // indent based on depth
    for (int i = 0; i < depth; i++) cout << "  ";
    // print node name
    cout << node->name << endl;

    for (Node* child : node->children) {
        printTree(child, depth + 1);
    }
}

int main() {
    // Create nodes
    Node* root = new Node("root");
    Node* home = new Node("home");
    Node* docs = new Node("documents");
    Node* pics = new Node("pictures");

    // Build tree
    root->children.push_back(home);
    home->children.push_back(docs);
    home->children.push_back(pics);

    // Traverse and print
    printTree(root);

    return 0;
}