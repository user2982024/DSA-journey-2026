#include <bits/stdc++.h>
using namespace std;

vector<string> reverseString(vector<string> &s, int n) {
    int start = 0;
    int end = n - 1;

    while (start < end) {
        swap(s[start], s[end]);
        start ++;
        end --;
    }

    return s;
}

int main() {

    vector<string> s;

    s.push_back("a");
    s.push_back("b");
    s.push_back("r");
    s.push_back("a");
    s.push_back("r");

    reverseString(s, 5);

    for (int i = 0; i < s.size(); i ++) {
        cout << s[i] << " ";
    }

    return 0;
}


#include <iostream>
using namespace std;

int main() {
    cout << "return 0";
    return 0;
}
