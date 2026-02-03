#include <iostream>

using namespace std;

class vector{  
    public:
    vector(){
        capacity = 3;
        current_index = 0;
        arr = new int[capacity];

        cout << "Constructor called. Array allocated at " << arr << " with capacity " << capacity << endl;
    }  

    ~vector(){
        delete [] arr;
        cout << "Destructor called. Array deallocated at " << arr << endl;
    }

    vector(const vector& other){
        capacity = other.capacity;
        current_index = other.current_index;
        arr = new int[capacity];
        for(int i = 0; i < current_index; i++){
            arr[i] = other.arr[i];
        }
        cout << "Copy constructor called. Array allocated at " << arr << " with capacity " << capacity << endl;
    }

    void operator=(const vector& other){
        if(this != &other){
            delete [] arr; // Free existing resource

            capacity = other.capacity;
            current_index = other.current_index;
            arr = new int[capacity];
            for(int i = 0; i < current_index; i++){
                arr[i] = other.arr[i];
            }
            cout << "Copy assignment operator called. Array allocated at " << arr << " with capacity " << capacity << endl;
        }
    }
    
    void push_back(int data){
        if(current_index == capacity){
            cout << "Resizing from " << capacity << " to " << 2 * capacity << endl;
            int* temp = new int[2 * capacity];
            for(int i = 0; i < capacity; i++){
                temp[i] = arr[i];
            }
            delete [] arr;
            cout << "Array deallocated at " << arr << endl;
            arr = temp;
            capacity *= 2;
        }

        arr[current_index] = data;
        current_index++;
    }

    int size() {
        return current_index;
    }

    int& at(int index) {
        if(index < current_index) {
            return arr[index];
        }
        
        throw out_of_range("Index out of range");
    }

    private:
    int* arr;
    int capacity;
    int current_index;
};

void function(){
    vector v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    //v.push_back(40);

    vector v2 = v; // Copy constructor called (default shallow copy)

    v2.at(0) = 100; // Modifying v2 also affects v due to shallow copy

    v = v2; // Copy assignment operator called (default shallow copy)

    v2.at(1) = 200; // Modifying v2 also affects v due to shallow copy

    for(int i = 0; i < v.size(); i++){
        cout << v.at(i) << endl;
    }
}

int main(){

    function();
    function();
    function();

    return 0;
}