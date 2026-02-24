#include <iostream>
#include <string>

using namespace std;

int getValue() {
    return 42;
}

int main() {

    int a = 10;          // 'a' is an lvalue
    int b = a;           // 'a' is an lvalue expression

    int c = 5 + 3;       // (5 + 3) is an rvalue (temporary)
    int d = getValue();  // return value is an rvalue (prvalue)

    int&& r1 = 100;      // 100 is an rvalue
    int&& r2 = a + 1;    // (a + 1) is an rvalue

    int&& r1 = 100;

    //int&& r2 = r1;        // ERROR
    int&& r3 = std::move(r1);  // OK

    cout << "Done\n";
}