/*
DAY 1 — ARRAYS + HASHING
Problem 5: Valid Anagram
Platform: LeetCode
Topic: frequency counting

SOURCE:
https://leetcode.com/problems/valid-anagram/

====================================================================
MY APPROACH
====================================================================
Two strings are anagrams only if:
    1. Their lengths are equal.
    2. Every character has the same frequency in both strings.

I first considered sorting both strings:
    sort(s.begin(), s.end())
    sort(t.begin(), t.end())

That works, but costs O(n log n).

I then used a frequency map:
    character -> frequency

First:
    Increase the frequency for every character in s.

Second:
    Decrease the frequency for every character in t.

For a valid anagram, the frequencies must balance.

====================================================================
MY ORIGINAL CODE
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> freqMap;
        int m = s.length();
        int n = t.length();

        if (m != n) {
            return false;
        }

        for (int i = 0; i < m; i++) {
            freqMap[s[i]]++;
        }

        for (int j = 0; j < n; j++) {
            if (freqMap.find(t[j]) != freqMap.end()) {
                freqMap[t[j]]--;
            }
        }

        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if (it->second > 0) {
                return false;
            }
        }

        return true;
    }
};

/*
====================================================================
IMPORTANT IMPROVEMENT
====================================================================
The original solution works after the length check, but the second
loop can be made more explicit:

    if (freqMap.find(t[j]) == freqMap.end())
        return false;

Then decrement.

That immediately rejects a character that appears in t but not s.

A further simplification is possible by adding for s and subtracting
for t in the same loop, then checking that every frequency is zero.

====================================================================
COMPLEXITY
====================================================================
Time:
    O(n) average

Space:
    O(k), where k = number of distinct characters.

If the character set is fixed (e.g. 26 lowercase letters), this can
be treated as O(1) auxiliary space.

====================================================================
KEY LESSON
====================================================================
Frequency hashing can compare two collections without sorting.

Pattern:
    first collection -> +frequency
    second collection -> -frequency
    all balances zero -> match
*/
