#include <iostream>
#include <list>

using namespace std;

class MyQueue{
    public:
    void push(int data){
        l.push_back(data);
    }

    void pop(){
        l.pop_front();
    }

    int& front(){
        return l.front();
    }

    int& back(){
        return l.back();
    }

    unsigned int size(){
        return l.size();
    }

    bool empty(){
        return l.size() == 0;
    }

    private:
    list<int> l;

};

int main(){
    MyQueue q;

    q.push(3);
    q.push(5);
    q.push(7);

    while(!q.empty()){
        cout << q.front() << endl;
        q.pop();
    }

    return 0;
}