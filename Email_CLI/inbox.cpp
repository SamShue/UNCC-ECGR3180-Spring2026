#include "inbox.h"
#include <iostream>
#include <utility>

using namespace std;

Inbox::Inbox() : count(0) {}

bool Inbox::push(const Email& e) {
    if (count >= CAPACITY) {
        cout << "[Inbox] push failed: inbox is full.\n";
        return false;
    }
    inbox[count] = e;
    count++;
    return true;
}

bool Inbox::pop() {
    if (count == 0) {
        cout << "[Inbox] pop failed: inbox is empty.\n";
        return false;
    }
    count--;
    return true;
}

bool Inbox::remove(int index) {
    if (!validIndex(index)) {
        cout << "[Inbox] remove failed: index " << index << " is out of range.\n";
        return false;
    }
    for (int i = index; i < count - 1; i++)
        inbox[i] = inbox[i + 1];
    count--;
    return true;
}

int Inbox::num_emails() const {
    return count;
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
    return index >= 0 && index < count;
}

void Inbox::sortByDate() {
    // Insertion sort — newest first (descending toInt())
    for (int i = 1; i < count; i++) {
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
    for (int i = 1; i < count; i++) {
        Email key = std::move(inbox[i]);
        int j = i - 1;
        while (j >= 0 && inbox[j].isRead() && !key.isRead()) {
            inbox[j + 1] = std::move(inbox[j]);
            j--;
        }
        inbox[j + 1] = std::move(key);
    }
}