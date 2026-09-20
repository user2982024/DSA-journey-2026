#include <bits/stdc++.h>
using namespace std;

string replaceSpaces(string &s, int n) {
    string temp = " ";

    for (int i = 0; i < n; i ++) {
        if (s[i] == ' ') {
            temp.push_back('@');
            temp.push_back('4');
            temp.push_back('0');
        }

        else {
            temp.push_back(s[i]);
        }
    }

    return temp;
}

int main() {

    string s = "We are One";

    string ans = replaceSpaces(s, 10);

    for (int i = 0; i < ans.length(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}