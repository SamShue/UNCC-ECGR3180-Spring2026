// Class for storing high scores ordered within in an array
// Minimal GameEntry class for demonstration
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class GameEntry {
    private:
        string name;
        int score;
    public:
        GameEntry(const string& n = "", int s = 0) : name{n}, score{s} {}
        string get_name() const { return name; }
        int get_score() const { return score; }
};

// Class for storing high scores ordered within in an array
class Scoreboard {
  private:
    int capacity;                     // capacity of the array
    int num_entries{0};               // number of actual entries
    GameEntry* board;                 // pointer to array of game entries

  public:
    // Constructs an empty scoreboard with the given capacity for storing entries
    Scoreboard(int cap = 10) : capacity{cap}, board{new GameEntry[cap]} {}
        
    // Returns the capacity of the scoreboard
    int get_capacity() const { return capacity; }

    // Returns the number of current entries stored
    int get_num_entries() const { return num_entries; }

    // Returns a reference to the entry at index i
    const GameEntry& get_entry(int i) const { return board[i]; }

    // Attempts to add a new score to the scoreboard (if it is high enough)
    void add(int score, const string& name) {
        // is the new entry e really a high score?
        if (num_entries < capacity || score > board[num_entries - 1].get_score()) {
            if (num_entries < capacity)            // no score drops from the board
                num_entries++;                     // so overall number increases

            // shift any lower scores rightward to make room for the new entry
            int j = num_entries - 1;               // index where last entry should be
            while (j > 0 && board[j - 1].get_score() < score) {
                board[j] = board[j - 1];           // shift entry from j-1 to j
                j--;                               // and decrement j
            }
            board[j] = GameEntry(name, score);     // when done, add new entry
        }
    }

    // Removes and returns the scoreboard entry at index i
    GameEntry remove(int i) {
        if (i < 0 || i >= num_entries) throw out_of_range("Invalid index");
        GameEntry temp{board[i]};                  // save the entry to be removed

        // shift entries to the right of the removed one to the left
        for (int j = i; j < num_entries - 1; j++)  // count up from i
            board[j] = board[j + 1];
        num_entries--;
        return temp;
    }
};  // end of Scoreboard class

// Demo main function
int main() {
    Scoreboard sb(5); // scoreboard with capacity 5
    sb.add(100, "Alice");
    sb.add(200, "Bob");
    sb.add(150, "Charlie");
    sb.add(180, "Diana");
    sb.add(120, "Eve");
    sb.add(170, "Frank"); // Should only be added if high enough

    cout << "High Scores:\n";
    for (int i = 0; i < sb.get_num_entries(); ++i) {
        const GameEntry& entry = sb.get_entry(i);
        cout << i+1 << ". " << entry.get_name() << ": " << entry.get_score() << endl;
    }

    cout << "\nRemoving 3rd entry...\n";
    GameEntry removed = sb.remove(2);
    cout << "Removed: " << removed.get_name() << ", Score: " << removed.get_score() << endl;

    cout << "\nHigh Scores after removal:\n";
    for (int i = 0; i < sb.get_num_entries(); ++i) {
        const GameEntry& entry = sb.get_entry(i);
        cout << i+1 << ". " << entry.get_name() << ": " << entry.get_score() << endl;
    }

    return 0;
}