#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Task 1
void taskA() {
    for (int i = 1; i <= 5; i++) {
        cout << "Task A: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

// Task 2
void taskB() {
    for (int i = 1; i <= 5; i++) {
        cout << "Task B: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    cout << "Starting threads..." << endl;

    thread t1(taskA);
    thread t2(taskB);

    t1.join();
    t2.join();

    cout << "Threads finished." << endl;
    return 0;
}
