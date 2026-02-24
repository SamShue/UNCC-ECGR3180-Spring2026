#include <iostream>
using namespace std;


// Simple class that manages an int on the heap
class HeapInt {
    int* value;
public:
    HeapInt(int v = 0) : value(new int(v)) {}

    // Rule of 3:
    HeapInt(const HeapInt& other) : value(new int(*other.value)) {}

    ~HeapInt() { delete value; }

    void operator=(const HeapInt& other) {
        if (this != &other) {
            delete value;
            value = new int(*other.value);
        }
    }

    // Rule of 5 (C++11 and later):
    HeapInt(HeapInt&& other) noexcept : value(other.value) {
        other.value = nullptr;
    }

    HeapInt& operator=(HeapInt&& other) noexcept {
        if (this != &other) {
            delete value;
            value = other.value;
            other.value = nullptr;
        }
        return *this;
    }

    // Accessor and mutator
    int get() const { return *value; }
    void set(int v) { *value = v; }

    // Comparison operator for sorting
    bool operator<(const HeapInt& other) const {
        return *value < *other.value;
    }
};

// Sorts an array of n elements
template <typename T>
void insertion_sort(T data[], int n) {
    for (int k = 1; k < n; k++) {
        T cur{data[k]};
        int j{k};
        while (j > 0 && cur < data[j - 1]) {
            data[j] = std::move(data[j - 1]);
            j--;
        }
        data[j] = std::move(cur);
    }
}

int main() {
    HeapInt arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; ++i) 
        cout << arr[i].get() << ' ';
    cout << endl;

    insertion_sort(arr, n);

    cout << "Sorted array:   ";
    for (int i = 0; i < n; ++i) 
        cout << arr[i].get() << ' ';
    cout << endl;
    return 0;
}
