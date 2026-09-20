#include <bits/stdc++.h>
using namespace std;

int main() {

    // A set contains only distinct values but a multiset can contain multiple copies of a single value.

    multiset<int> s;

    s.insert(5);
    s.insert(5);
    s.insert(5);

    // s.erase(5);              // Removes all copies of the value.

    s.erase(s.find(5));         // Removes only one copy of the element.

    cout << s.count(5) << "\n";

    return 0;
}