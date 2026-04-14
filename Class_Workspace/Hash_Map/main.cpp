#include <iostream>
#include <stdexcept>

using namespace std;

class HashMap{
    public:

    HashMap(){
        size = 50;
        arr = new Bucket*[size];

        for(int i = 0; i < size; i++){
            arr[i] = nullptr;
        }
    }

    int& operator[](string key) const {
        unsigned int index = hash(key);

        Bucket* curr = arr[index];
        while(curr != nullptr){
            if(curr->key == key){
                return curr->value;
            }
            curr = curr->next;
        }
        throw out_of_range("Key not found");
    }

    void insert(string key, int value){
        unsigned int index = hash(key);

        if(arr[index] == nullptr){
            arr[index] = new Bucket(key, value);
        } else {
            Bucket* curr = arr[index];
            while(curr->next != nullptr){
                curr = curr->next;
            }
            curr->next = new Bucket(key, value);
        }
    }

    void print() const {
        for(int i = 0; i < size; i++){
            if(arr[i] == nullptr)
                continue;

            Bucket* curr = arr[i];
            while(curr != nullptr){
                cout << "Key: " << curr->key << ", Value: " << curr->value << endl;
                curr = curr->next;
            }
        }
    }

    private:

    struct Bucket {
        Bucket(string key, int value){
            this->key = key;
            this->value = value;
            this->next = nullptr;
        }

        string key;
        int value;
        Bucket* next;
    };

    unsigned int size;
    Bucket** arr;

    unsigned int hash(string key) const {
        unsigned int sum = 0;
        for(int i = 0; i < key.size(); i++){
            sum += key[i];
        }
        return sum % size;
    }


};

int main(){

    HashMap map;

    map.insert("Hello", 5);
    map.insert("World", 10); // Collision
    map.insert("LargerWord", 15);

    map.print();

    return 0;
}