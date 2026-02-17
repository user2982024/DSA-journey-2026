/*
===============================================================
Problem: Reverse a String (In-place)
Sheet: Love Babbar 450 DSA Sheet
Question Number: 1
Topic: Arrays / Strings / Two Pointers
Difficulty: Easy
Author: Sheikh Abrar
Journey: 100 Days of DSA
===============================================================

🧩 Problem Statement:
Given a string, reverse it in place and return the reversed string.

Example:
Input:  "hello"
Output: "olleh"

---------------------------------------------------------------
🧠 Approach: Two Pointer Technique (Optimal)

We use two pointers:
- One at the beginning of the string
- One at the end of the string

We swap the characters at both positions and move inward.

Steps:
1. Initialize start = 0 and end = length - 1
2. Swap characters at start and end
3. Increment start and decrement end
4. Continue until start < end

Why start < end and NOT start <= end?
If the string length is odd, when start == end,
both pointers point to the middle element.

Swapping an element with itself is unnecessary,
so we avoid an extra redundant swap.

---------------------------------------------------------------
🔍 Dry Run:

String = "abcde"

start = 0, end = 4 → swap a ↔ e → ebcda
start = 1, end = 3 → swap b ↔ d → edcba
start = 2, end = 2 → stop

Final = "edcba"

---------------------------------------------------------------
⏱ Time Complexity:
O(n)
We traverse roughly half the string, but in Big-O → O(n)

🧠 Space Complexity:
O(1)
Reversal is done in-place with no extra memory.

---------------------------------------------------------------
✅ Edge Cases Handled:
- Empty string
- Single character string
- Even length string
- Odd length string
- Special characters

---------------------------------------------------------------
⭐ Key Learning:
Two-pointer technique is widely used for:
- Reversal problems
- Palindrome checking
- Pair searching
- Partitioning problems

===============================================================
*/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string reverseString(string &s) {

        // Length of string
        int n = s.length();

        // Two pointers
        int left = 0;
        int right = n - 1;

        // Swap characters while pointers don't meet
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }

        return s;
    }
};

int main() {

    Solution obj;

    string s;

    cout << "Enter a string: ";
    cin >> s;

    cout << "Original string: " << s << endl;

    string reversed = obj.reverseString(s);

    cout << "Reversed string: " << reversed << endl;

    return 0;
}