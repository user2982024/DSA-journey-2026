#include <bits/stdc++.h>
using namespace std;

string removeAdjacentDuplicates(string &s, int n) {
    int j = 0;
    int i = 1;

    while (i < n - 1 && j < n) {
        if (s[j] == s[i]) {
            s.erase(j, 2);
            j = i + 1;
            i = j + 1;
        }

        else if (s[i] == s[i + 1]) {
            s.erase(i, 2);
            i = j + 1;
        }

        else {
            i ++;
            j ++;
        }
    }

    return s;
}


// string removeAdjacentDuplicates(string &s, int n) {              //  This function is to remove duplicates not adjacent duplicates
    // unordered_set<char> us;
    // string temp = " ";

    // for (int i = 0; i < n; i ++) {
    //     if (us.find(s[i]) != us.end()) {
    //         us.erase(s[i]);
    //     }

    //     else {
    //         us.insert(s[i]);
    //     }
    // }

    // for (auto x : us) {
    //     temp.push_back(x);
    // }

    // return temp;
// }

int main() {

    string s = "asddffhkkloo";

    string ans = removeAdjacentDuplicates(s, 12);

    cout << ans << "\n";

    return 0;
}