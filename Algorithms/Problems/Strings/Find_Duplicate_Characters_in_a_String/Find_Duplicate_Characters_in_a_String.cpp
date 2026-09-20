#include <bits/stdc++.h>
using namespace std;

string findDuplicateCharacters(string &s, int n) {
    // unordered_map<char, int> freqMap;
    // string ans = "";

    // for (int i = 0; i < n; i ++) {
    //     freqMap[s[i]] ++;
    // }

    // for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
    //     if (it->second > 1) {
    //         ans.push_back(it->first);
    //     }
    // }

    // return ans;



    unordered_set<char> us;
    string ans = "";

    for (int i = 0; i < n; i ++) {
        if (us.find(s[i]) == us.end()) {
            us.insert(s[i]);
        }

        else {
            ans.push_back(s[i]);
        }
    }

    return ans;
}

int main() {
    string s = "abcabdeef";

    string ans = findDuplicateCharacters(s, 9);

    cout << ans << "\n";
}