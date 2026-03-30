#include <list>
#include <iterator>
#include <iostream>

using namespace std;

list<int> mergeLists(list<int>& left, list<int>& right){
    list<int> result;

    while(!left.empty() && !right.empty()){
        if(left.front() <= right.front()){
            result.push_back(left.front());
            left.pop_front();
        } else {
            result.push_back(right.front());
            right.pop_front();
        }
    }

    result.splice(result.end(), left);
    result.splice(result.end(), right);

    return result;
}

list<int> mergeSort(list<int> lst){
    if(lst.size() <= 1){
        return lst;
    }

    list<int> left;
    list<int> right;

    auto mid = lst.begin();
    advance(mid, lst.size()/2);

    // parameters: destination (list), source (list), start (iterator), end (iterator)
    left.splice(left.begin(), lst, lst.begin(), mid);
    right.splice(right.begin(), lst, mid, lst.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return mergeLists(left, right);
}

int main() {

    list<int> numbers = {8, 3, 6, 2, 7, 1, 4, 5};

    // Sort the list using merge sort from smaller to larger
    numbers = mergeSort(numbers);

    for (auto it = numbers.begin(); it != numbers.end(); it++){
        cout << *it << endl;
    }
    cout << endl;
}