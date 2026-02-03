#include <iostream>

using namespace std;

struct Complex {
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0) {
        real = r;
        imag = i;
    }

    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }

    Complex add(Complex other) const {
        Complex result;
        result.real = real + other.real;
        result.imag = imag + other.imag;
        return result;
    }

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    bool operator==(const Complex& other) const;
};

Complex Complex::operator+(const Complex& other) const {
    Complex result;
    result.real = real + other.real;
    result.imag = imag + other.imag;
    return result;
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

bool Complex::operator==(const Complex& other) const {
    return (real == other.real) && (imag == other.imag);
}

int main() {
    // (3 + 5i) + (2 + 7i) = (5 + 12i)
    Complex c1(3, 5);
    Complex c2(2, 7);
    Complex sum;

    sum = c1.add(c2); // Using member function to add
    sum = c1 + c2; // Using operator overloading to add
    Complex result = c1 - c2; // Using operator overloading to subtract

    sum.print();

    if(c1 == c2) {
        cout << "c1 is equal to c2" << endl;
    } else {
        cout << "c1 is not equal to c2" << endl;
    }
    
    return 0;
}