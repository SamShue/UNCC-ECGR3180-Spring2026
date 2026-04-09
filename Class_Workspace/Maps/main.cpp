#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

string toLower(string word) {
    for (char& c : word)
        c = tolower(c);
    return word;
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

        cout << word << endl;

    }
    file.close();

    return 0;
}
