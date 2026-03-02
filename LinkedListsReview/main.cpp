#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
    public:
    SinglyLinkedList() : head(nullptr) {};

    ~SinglyLinkedList() {
        Node* current = head;
        while(current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr) {
        if(other.head == nullptr){
            return;
        }

        head = new Node(other.head->data);
        Node* currentOther = other.head->next;
        Node* currentThis = head;

        while(currentOther != nullptr){
            currentThis->next = new Node(currentOther->data);
            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }
    }

    void operator=(const SinglyLinkedList& other) {
        if(this == &other){
            return;
        }

        // Clean up existing nodes
        Node* current = head;
        while(current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;

        if(other.head == nullptr){
            return;
        }

        head = new Node(other.head->data);
        Node* currentOther = other.head->next;
        Node* currentThis = head;

        while(currentOther != nullptr){
            currentThis->next = new Node(currentOther->data);
            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }
    }

    void push_back(int value){
        if(head == nullptr){
            head = new Node(value);
            return;
        }

        Node* current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = new Node(value);
    }

    void insert(unsigned int index, int value){
        if(index == 0){
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        unsigned int count = 0;
        while(current != nullptr && count < index - 1){
            count++;
            current = current->next;
        }

        if(current == nullptr){
            throw out_of_range("Index out of range");
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(unsigned int index){
        if(head == nullptr){
            throw out_of_range("Index out of range");
        }

        if(index == 0){
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        unsigned int count = 0;
        while(current != nullptr && count < index - 1){
            count++;
            current = current->next;
        }

        if(current == nullptr || current->next == nullptr){
            throw out_of_range("Index out of range");
        }

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    unsigned int size() const {
        unsigned int count = 0;
        Node* current = head;
        while(current != nullptr){
            count++;
            current = current->next;
        }
        return count;
    }

    int& at(unsigned int index) {
        Node* current = head;
        unsigned int count = 0;
        while(current != nullptr){
            if(count == index){
                return current->data;
            }
            count++;
            current = current->next;
        }
        throw out_of_range("Index out of range");
    }

    private:
    Node* head;

};

int main(){
    SinglyLinkedList myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    myList.insert(1, 15); // Insert 15 at index 1
    myList.remove(2); // Remove element at index 2 (which is 20)

    for (int i = 0; i < myList.size(); i++) {
        cout << myList.at(i) << endl;
    }

    return 0;
}