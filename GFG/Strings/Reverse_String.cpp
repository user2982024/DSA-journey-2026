#include <bits/stdc++.h>
using namespace std;

// Function to reverse a string using two pointers
string reverseString(string &s) {
    int start = 0;
    int end = s.length() - 1;

    while (start < end) {
        swap(s[start], s[end]);
        start++;
        end--;
    }
    return s;
}

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);

    string result = reverseString(s);
    cout << "Reversed string: " << result << endl;

    return 0;
}
