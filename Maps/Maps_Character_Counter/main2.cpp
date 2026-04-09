#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Poor implementation: O(n) search every insert/lookup
vector<pair<string, int>> data;

string toLower(string word) {
    for (char& c : word)
        c = tolower(c);
    return word;
}

// Scans the entire vector to find the key. Returns index, or -1 if not found.
int find(string key) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].first == key)
            return i;
    }
    return -1;
}

void insert(string key, int value) {
    data.push_back({key, value});
}

int get(string key) {
    int i = find(key);
    if (i == -1)
        return -1;
    return data[i].second;
}

void set(string key, int value) {
    int i = find(key);
    if (i != -1)
        data[i].second = value;
}

void print() {
    for (auto& pair : data) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    ifstream file("test.txt");
    if (!file.is_open()) {
        cout << "Error: could not open file" << endl;
        return 1;
    }

    string word;
    while (file >> word) {
        word = toLower(word);
        if (find(word) != -1)
            set(word, get(word) + 1);
        else
            insert(word, 1);
    }
    file.close();

    print();

    return 0;
}
