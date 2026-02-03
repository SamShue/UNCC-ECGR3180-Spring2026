#include "student.h"

Student::Student(string n, double g, int i){
    setName(n);
    setGpa(g);
    setId(i);
}

void Student::setName(string name){
    if(name == "Butt"){
        cout << "Invalid name!" << endl;
        name = "Invalid";
        return;
    }

    Student::name = name;
}

string Student::getName() const {
    return name;
}

void Student::setGpa(double gpa){
    if(gpa < 0.0 || gpa > 4.0){
        cout << "Invalid GPA value assigned." << endl;
        gpa = -1.0;
        return;
    }

    Student::gpa = gpa;
}

double Student::getGpa() const {
    return gpa;
}

void Student::setId(int id){
    if(id <= 0){
        cout << "Invalid ID value assigned." << endl;
        id = -1;
        return;
    }

    Student::id = id;
}

int Student::getId() const {
    return id;
}

void Student::print() const {
    cout << "Name: " << name << ", GPA: " << gpa << ", ID: " << id << endl;
}
