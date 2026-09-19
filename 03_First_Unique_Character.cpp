/*
DAY 1 — ARRAYS + HASHING
Problem 3: First Unique Character in a String
Platform: LeetCode
Topic: frequency map + original order

SOURCE:
https://leetcode.com/problems/first-unique-character-in-a-string/

====================================================================
MY APPROACH
====================================================================
I need two different pieces of information:

1. Frequency:
       How many times does each character occur?

2. Original order:
       Which unique character appears first?

Therefore:
    unordered_map<char, int> -> frequency
    original string           -> order

First pass:
    Build the frequency map.

Second pass:
    Traverse the ORIGINAL string from left to right.
    The first character whose frequency is 1 is the answer.

====================================================================
MY ORIGINAL CODE
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> freqMap;
        int n = s.length();

        for (int i = 0; i < n; i++) {
            freqMap[s[i]]++;
        }

        for (int i = 0; i < n; i++) {
            if (freqMap[s[i]] == 1) {
                return i;
            }
        }

        return -1;
    }
};

/*
====================================================================
WHY NOT TRAVERSE THE unordered_map?
====================================================================
unordered_map does not guarantee the original order of elements.

For "first unique", order matters.

The map answers:
    "Is this character unique?"

The original string answers:
    "Which unique character comes first?"

Therefore we traverse the original string in the second pass.

====================================================================
COMPLEXITY
====================================================================
Let k = number of distinct characters.

Time:
    O(n) average

Space:
    O(k)

For a fixed alphabet such as lowercase English letters, k <= 26,
so the auxiliary space can be considered O(1).

====================================================================
KEY LESSON
====================================================================
Hashing can provide information, while the original array/string
can preserve the order that hashing does not guarantee.

Pattern:
    frequency + original order
*/
