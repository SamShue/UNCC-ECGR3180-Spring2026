#include <iostream>

using namespace std;

class MyMap{
    public:
    MyMap(){
        size = 10;
        arr = new Bucket[size];
    }

    void insert(string key, int value){
        int index = toIndex(key);
        arr[index].key = key;
        arr[index].value = value;
    }

    int& operator[] (string key) const{
        return arr[toIndex(key)].value;
    } 

    void print() const{
        cout << "MyMap contents:" << endl;
        for(int i = 0; i < size; i++){
            cout << "Key: " << arr[i].key << ", Value: " << arr[i].value << endl;
        }
    }

    private:
    struct Bucket{
        string key;
        int value;
    };

    unsigned int toIndex(string s) const {
        unsigned int sum = 0;
        for(char c : s){
            sum += c;
        }
        return sum % size;
    }

    unsigned int size;
    Bucket* arr;
};

int main(){

    MyMap map;

    map.insert("Butts", 7);
    map.insert("Hello", 5); // Collision with "Butts"
    map.insert("Coffee", 3);

    map.print();

    return 0;
}