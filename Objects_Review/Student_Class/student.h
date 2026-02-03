#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student {
    public:
    Student(string n, double g, int i);
    void setName(string name);
    string getName() const;
    void setGpa(double gpa);
    double getGpa() const;
    void setId(int id);
    int getId() const;
    void print() const;

    private:
    string name;
    double gpa;
    int id;
};

#endif