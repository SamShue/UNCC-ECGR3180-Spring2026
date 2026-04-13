#include <iostream>

using namespace std;

class MyMap{
    public:
    MyMap(){
        size = 10;
        arr = new Bucket[size];
    }

    void insert(string key, int value){
        int 

    }

    int& operator[] (string key) const{
        return arr[toIndex(key)].value;
    } 

    void print() const{
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
        return sum;
    }

    unsigned int size;
    Bucket* arr;
};

int main(){

    MyMap map;

    map.insert("Butts", 7);
    map.insert("Hello", 3);

    map.print();

    return 0;
}