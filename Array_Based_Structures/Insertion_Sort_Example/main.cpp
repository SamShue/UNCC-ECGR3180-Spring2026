#include <iostream>
using namespace std;

// Sorts an array of n elements
template <typename T>
void insertion_sort(T data[], int n) {
    for (int k = 1; k < n; k++) {
        T cur{data[k]};
        int j{k};
        while (j > 0 && cur < data[j - 1]) {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = cur;
    }
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    //string arr[] = {"banana", "apple", "cherry", "date", "fig", "grape"};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';
    cout << endl;

    insertion_sort(arr, n);

    cout << "Sorted array:   ";
    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
