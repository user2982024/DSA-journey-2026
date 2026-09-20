#include <bits/stdc++.h>
using namespace std;

int main() {

    set<int> s;

    // All set operations can also be performed on unordered_set.

    s.insert(3);
    s.insert(2);
    s.insert(5);

    s.erase(3);
    s.insert(4);

    // cout << s.count(3) << "\n";
    // cout << s.count(4) << "\n";

    s.insert(10);
    s.insert(10);
    s.insert(10);

    // cout << s.count(10) << "\n";

    // Not possible to access set elements like a vector using [] notation.

    // cout << s.size() << "\n";

    // for (auto x : s) {
    //     cout << x << "\n";
    // }

    // for (auto it = s.begin(); it != s.end(); it ++) {
    //     cout << *it << "\n";
    // }

    // bool found = false;
    // if (s.find(10) != s.end()) {
    //     found = true;
    // }

    // cout << found << "\n";

    // There are 2 types of sets, first one is 'set' which maintains the order of the elements and the second one is 'unordered_set', which doesn't maintain the order of the elements. 

    // auto smallest = s.begin();
    // auto largest = s.end();
    // largest --;

    // cout << "The smallest set element is: " << *smallest << "\n";
    // cout << "The largest set element is: " << *largest << "\n";

    return 0;
}