#include <bits/stdc++.h>
using namespace std;

string reverseString(string str, int s, int e) {
    if (s >= e) {
        return str;
    }

    swap(str[s], str[e]);
    return reverseString(str, s + 1, e - 1);
}

int main() {
    string str = "abrar";

    string ans = reverseString(str, 0, 4);
    cout << ans << "\n";

    return 0;
}