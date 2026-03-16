#pragma once
#include <string>
#include <vector>
#include "email_server.h"

class Inbox {
public:
    Inbox();

    bool push(const Email& e);  // append to end
    bool pop();                 // remove last; returns false if empty
    bool remove(int index);     // remove at 0-based index

    int              num_emails() const;
    const Email&     getEmail(int index) const;
    void             markRead(int index);

    void sortByDate();       // sorts emails by date (newest first)
    void sortByReadStatus(); // sorts emails by read status (Unread first)

private:
    std::vector<Email> inbox;

    bool validIndex(int index) const;
};
