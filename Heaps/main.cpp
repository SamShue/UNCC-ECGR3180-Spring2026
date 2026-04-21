#include <iostream>
#include <vector>
#include <algorithm>

// Function to maintain the min-heap property
void minHeapify(std::vector<int>& arr, int n, int i) {
    int smallest = i;         // Initialize smallest as root
    int left = 2 * i + 1;    // Left child index
    int right = 2 * i + 2;   // Right child index

    // If left child is smaller than current smallest
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than current smallest
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // If smallest is not root, swap and continue heapifying
    if (smallest != i) {
        std::swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(std::vector<int>& arr) {
    int n = arr.size();

    // Start from last non-leaf node and move upward
    for (int i = n/2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

int main() {
    std::vector<int> arr = {10, 3, 8, 4, 5, 1};

    buildMinHeap(arr);

    std::cout << "Min-Heap: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}