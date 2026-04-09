#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

string toLower(string word) {
    for (char& c : word)
        c = tolower(c);
    return word;
}

int main() {
    map<string, int> wordCount;

    ifstream file("test.txt");
    if (!file.is_open()) {
        cout << "Error: could not open file" << endl;
        return 1;
    }

    string word;
    while (file >> word) {
        word = toLower(word);
        wordCount[word]++;
    }
    file.close();

    for (const auto& entry : wordCount) {
        cout << entry.first << ": " << entry.second << endl;
    }

    return 0;
}
