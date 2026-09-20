#include <bits/stdc++.h>
using namespace std;

int main() {

    // All map operations can also be done on unordered_map, but unordered_map is faster than map.

    map<string, int> m;

    m["monkey"] = 4;
    m["banana"] = 3;
    m["harpsichord"] = 9;

    // cout << m["banana"] << "\n";
    // cout << m["aybabtu"] << "\n";

    // bool found = false;
    // if (m.count("banana")) {
    //     found = true;
    // }

    // cout << found << "\n";

    // for (auto x : m) {
    //     cout << x.first << " " << x.second << "\n";
    // }

    for (auto it = m.begin(); it != m.end(); it ++) {
        cout << it->first << " " << it->second << "\n";
    }

    return 0;
}