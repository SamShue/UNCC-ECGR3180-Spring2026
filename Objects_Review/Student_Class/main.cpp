#include <iostream>
#include "student.h"

using namespace std;

int main(){
    Student s("Alice", 3.8, 12345);
    s.print();

    Student s2("Butt", 4.5, -10);
    s2.print();

    return 0;
}