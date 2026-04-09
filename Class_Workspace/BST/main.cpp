#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
    public:
    BST(){
        root = nullptr;
    }

    void insert(int val){
        Node* newNode = new Node(val);

        if(root == nullptr){
            root = newNode;
            return;
        }

        Node* current = root;
        while(true){
            if(val < current->data){
                if(current->left == nullptr){
                    current->left = newNode;
                    return;
                }
                current = current->left;
            } else if(val > current->data){
                if(current->right == nullptr){
                    current->right = newNode;
                    return;
                }
                current = current->right;
            } else {
                delete newNode;
                return;
            }
        }
    }

    bool search(int val) const {
        Node* current = root;
        while(current != nullptr){
            if(val == current->data){
                return true;
            } else if(val < current->data){
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void printInOrder(Node* current) const {
        if(current == nullptr)
            return;

        printInOrder(current->left);
        cout << current->data << " ";
        printInOrder(current->right);
    }

    void printInOrder() const {
        cout << "In-order: ";
        printInOrder(root);
        cout << endl;
    }

    private:
    Node* root;
};

int main() {
    
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(7);
    bst.insert(20);
    bst.insert(15);
    bst.insert(25);
    bst.insert(3);
    bst.insert(27);

    bst.printInOrder();

    cout << "Searching for 20: " << bst.search(20) << endl;
    cout << "Searching for 21: " << bst.search(21) << endl;

    return 0;
}