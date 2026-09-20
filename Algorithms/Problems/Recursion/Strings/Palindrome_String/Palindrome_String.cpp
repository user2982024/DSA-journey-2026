#include <bits/stdc++.h>
using namespace std;

bool checkPalindromeString(string &str, int s, int e) {
    if (s >= e) {
        return true;
    }

    if (str[s] != str[e]) {
        return false;
    }

    return checkPalindromeString(str, s + 1, e - 1);
}

int main() {
    string str = "abccba";
    int start = 0;
    int end = 5;

    bool ans = checkPalindromeString(str, start, end);
    cout << ans << "\n";

    return 0;
}