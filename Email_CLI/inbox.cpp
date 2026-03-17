#include "inbox.h"
#include <iostream>
#include <utility>

using namespace std;

Inbox::Inbox() {}

bool Inbox::push(const Email& e) {
    inbox.push_back(e);
    return true;
}

bool Inbox::pop() {
    if (inbox.empty()) {
        cout << "[Inbox] pop failed: inbox is empty.\n";
        return false;
    }
    inbox.pop_back();
    return true;
}

bool Inbox::remove(int index) {
    if (!validIndex(index)) {
        cout << "[Inbox] remove failed: index " << index << " is out of range.\n";
        return false;
    }
    inbox.erase(inbox.begin() + index);
    return true;
}

int Inbox::num_emails() const {
    return static_cast<int>(inbox.size());
}

const Email& Inbox::getEmail(int index) const {
    static Email empty("", "", "", "", false);
    if (!validIndex(index)) return empty;
    return inbox[index];
}

void Inbox::markRead(int index) {
    if (validIndex(index))
        inbox[index].markRead();
}

bool Inbox::validIndex(int index) const {
    return index >= 0 && index < static_cast<int>(inbox.size());
}

void Inbox::sortByDate() {
    // Insertion sort — newest first (descending toInt())
    int n = static_cast<int>(inbox.size());
    for (int i = 1; i < n; i++) {
        Email key = std::move(inbox[i]);
        int j = i - 1;
        while (j >= 0 && inbox[j].getDate().toInt() < key.getDate().toInt()) {
            inbox[j + 1] = std::move(inbox[j]);
            j--;
        }
        inbox[j + 1] = std::move(key);
    }
}

void Inbox::sortByReadStatus() {
    // Insertion sort — unread first (false sorts before true)
    int n = static_cast<int>(inbox.size());
    for (int i = 1; i < n; i++) {
        Email key = std::move(inbox[i]);
        int j = i - 1;
        while (j >= 0 && inbox[j].isRead() && !key.isRead()) {
            inbox[j + 1] = std::move(inbox[j]);
            j--;
        }
        inbox[j + 1] = std::move(key);
    }
}