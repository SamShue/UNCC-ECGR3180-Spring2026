#include <iostream>
#include <vector>

using namespace std;

class myStack{
    public:

    void push(char data){
        v.push_back(data);
    }

    void pop(){
        v.pop_back();
    }

    char& top(){
        return v.at(v.size() - 1);
    }

    unsigned int size(){
        return v.size();
    }

    private:
    vector<char> v;
};

int main(){
    myStack s;
    /*
    s.push(3);
    s.push(5);
    s.push(7);

    for(int i = 0; i < 3; i++){
        cout << s.top() << endl;
        s.pop();
    }
    */

    string input;
    getline(cin, input);

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '('){
            s.push('(');
            cout << "Pushing" << endl;
        }

        if(input[i] == ')'){
            s.pop();
            cout << "Popping" << endl;
        }
    }

    cout << s.size() << endl;
    if(s.size()){
        cout << "Imbalanced parenthesis!" << endl;
    } else {
        cout << "Balanced parenthesis!" << endl;
    }

    return 0;
}