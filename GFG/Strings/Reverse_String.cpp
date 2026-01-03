#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Reverse a String
    Source: Love Babbar DSA Sheet (Strings - Q1)

    Approach:
    → Use the two-pointer technique.
    → Initialize two pointers, start at the beginning and end at the last character.
    → Swap the characters at start and end, then move pointers towards the center.
    → Continue until start >= end.
    → This reverses the string in place.

    Time Complexity: O(n) — each character is visited once
    Space Complexity: O(1) — no extra space used apart from a few variables
*/

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
