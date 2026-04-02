#include <iostream>

using namespace std;

struct Node {
    int   data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root(nullptr) {}

    // Insert a value into the tree.
    // Traverses left if val is smaller, right if larger, until an empty spot is found.
    void insert(int val) {
        Node* newNode = new Node(val);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true) {
            if (val < current->data) {
                if (current->left == nullptr) { 
                    current->left  = newNode; 
                    return; 
                }
                current = current->left;
            } else if (val > current->data) {
                if (current->right == nullptr) { 
                    current->right = newNode; 
                    return; 
                }
                current = current->right;
            } else {
                // No duplicates allowed, clean up and return
                delete newNode; 
                return;
            }
        }
    }

    // Remove a value from the tree (no-op if not found).
    // Three cases: node is a leaf, has one child, or has two children.
    void remove(int val) {
        Node* parent  = nullptr;
        Node* current = root;

        // Step 1: Find the node to delete and track its parent.
        while (current != nullptr && current->data != val) {
            parent  = current;
            current = (val < current->data) ? current->left : current->right;
        }

        if (current == nullptr) return; // Value not found, nothing to do.

        // Step 2: Node has TWO children.
        // Find the in-order successor (smallest node in the right subtree),
        // copy its value here, then delete the successor instead.
        if (current->left != nullptr && current->right != nullptr) {
            Node* successorParent = current;
            Node* successor       = current->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor       = successor->left;
            }
            current->data = successor->data; // Overwrite with successor value.
            // Now re-target deletion at the successor node (which has at most one child).
            parent  = successorParent;
            current = successor;
        }

        // Step 3: Node has ZERO or ONE child.
        Node* child = (current->left != nullptr) ? current->left : current->right;

        if (parent == nullptr) // The parent is null if the node to delete is the root.
            root = child; // Deleting the root.
        else if (parent->left  == current) 
            parent->left  = child;
        else
            parent->right = child;

        delete current;
    }

    // Search for a value. Returns true if found.
    bool search(int val) const {
        Node* current = root;
        while (current != nullptr) {
            if (val == current->data) 
                return true;
            else if (val <  current->data) 
                current = current->left;
            else                           
                current = current->right;
        }
        return false;
    }

    // Print all values in sorted (ascending) order.
    void printInOrder(Node* node) const {
        if (node == nullptr) return;
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }

    void printInOrder() const {
        cout << "In-order: ";
        printInOrder(root);
        cout << "\n";
    }

private:
    Node* root;
};

int main() {
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "After inserting 50 30 70 20 40 60 80:\n";
    tree.printInOrder();

    cout << "\nSearch 40: " << (tree.search(40) ? "Found" : "Not found") << "\n";
    cout << "Search 99: " << (tree.search(99) ? "Found" : "Not found") << "\n";

    tree.remove(20); // leaf
    tree.remove(30); // one child
    tree.remove(50); // two children
    cout << "\nAfter removing 20, 30, 50:\n";
    tree.printInOrder();

    return 0;
}
