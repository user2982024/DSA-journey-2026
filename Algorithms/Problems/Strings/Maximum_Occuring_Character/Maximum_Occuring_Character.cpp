#include <bits/stdc++.h>
using namespace std;

char getMaxOccuringCharacter(string &s, int n) {
    unordered_map<char, int> freqMap;

    for (int i = 0; i < s.size(); i ++) {
        freqMap[s[i]] ++;
    }

    int maxCount = 0;
    char ans = 'x';

    for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
        if (it -> second > maxCount) {
            maxCount = it -> second;
            ans = it->first;
        }
    }

    return ans;
}

int main() {

    string s = "cccbbeerrrrrr";

    char ans = getMaxOccuringCharacter(s, 13);
    cout << ans << "\n";

    return 0;
}