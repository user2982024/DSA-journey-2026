#include <bits/stdc++.h>
using namespace std;

string removeAllOccurencesOfASubstring(string &s, int n, string part) {
    while (s.length() > 0 && s.find(part) < s.length()) {
        s.erase(s.find(part), part.length());
    }

    return s;
}

int main() {

    string s = "abvabcn";
    string part = "abc";

    string ans = removeAllOccurencesOfASubstring(s, 7, part);
    cout << ans << "\n";

    return 0;
}