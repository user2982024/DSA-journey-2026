#include <bits/stdc++.h>
using namespace std;

bool checkPalindrome(vector<string> &s, int n) {
    int start = 0;
    int end = n - 1;

    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }

        else {
            start ++;
            end --;
        }
    }

    return true;
}

int main() {

    vector<string> s;
    s.push_back("a");
    s.push_back("b");
    s.push_back("c");
    s.push_back("b");
    s.push_back("a");

    bool ans = checkPalindrome(s, 5);
    cout << ans << "\n";

    return 0;
}