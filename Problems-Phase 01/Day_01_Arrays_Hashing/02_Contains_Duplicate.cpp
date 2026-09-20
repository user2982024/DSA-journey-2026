/*
DAY 1 — ARRAYS + HASHING
Problem 2: Contains Duplicate
Platform: LeetCode
Topic: unordered_set / membership checking

SOURCE:
https://leetcode.com/problems/contains-duplicate/

====================================================================
MY APPROACH
====================================================================
I use an unordered_set because I do not need the frequency of an
element. I only need to know:

    "Have I already seen this element?"

For every element:
    1. Search for it in the set.
    2. If found, a duplicate exists -> return true.
    3. Otherwise insert it.
    4. If the whole array finishes, return false.

====================================================================
MY ORIGINAL CODE
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (seen.find(nums[i]) != seen.end()) {
                return true;
            }
            else {
                seen.insert(nums[i]);
            }
        }

        return false;
    }
};

/*
====================================================================
IMPORTANT CORRECTION FROM MY EXPLANATION
====================================================================
unordered_set::find() does NOT return n.

find(x) returns an iterator.

If x is NOT present:
    seen.find(x) == seen.end()

If x IS present:
    seen.find(x) != seen.end()

The code above uses this correctly.

====================================================================
WHY unordered_set AND NOT unordered_map?
====================================================================
We do not need:
    element -> frequency

We only need:
    element -> existence

Therefore unordered_set is sufficient.

Why not set?
    set            -> O(log n) operations
    unordered_set  -> O(1) average operations

The reason unordered_set is O(1) average is its hash-table
implementation, not merely the fact that it does not preserve order.

====================================================================
COMPLEXITY
====================================================================
Time:
    O(n) average

Space:
    O(n)

Worst-case hash-table operations can degrade, but O(n) average is
the standard interview analysis for this solution.

====================================================================
KEY LESSON
====================================================================
"Need to know whether I have seen a value?"
        |
        v
unordered_set
*/
