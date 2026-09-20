/*
DAY 1 — ARRAYS + HASHING
Problem 6: Intersection of Two Arrays
Platform: LeetCode
Topic: unordered_set / membership + uniqueness

SOURCE:
https://leetcode.com/problems/intersection-of-two-arrays/

====================================================================
MY APPROACH
====================================================================
The answer must contain UNIQUE values.

We do NOT need:
    - frequencies
    - original indices
    - sorted order

We only need:
    "Does this value exist in nums1?"

Therefore I use:
    unordered_set<int> seen

First pass:
    Insert every value from nums1 into the set.

Second pass:
    For each value in nums2:
        - If it exists in the set, add it to the answer.
        - Erase it immediately so it cannot be added again.

The erase step guarantees uniqueness in the answer.

====================================================================
MY ORIGINAL CODE
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> seen;
        vector<int> ans;
        int m = nums1.size();
        int n = nums2.size();

        for (int i = 0; i < m; i++) {
            seen.insert(nums1[i]);
        }

        for (int j = 0; j < n; j++) {
            if (seen.find(nums2[j]) != seen.end()) {
                ans.push_back(nums2[j]);
                seen.erase(nums2[j]);
            }
        }

        return ans;
    }
};

/*
====================================================================
WHY ERASE?
====================================================================
Suppose:
    nums1 = [1, 2, 2, 1]
    nums2 = [2, 2]

After the first 2 is found:
    add 2 to answer
    erase 2 from seen

The second 2 then cannot be found.

Therefore:
    answer = [2]

This enforces the "unique values only" requirement.

====================================================================
COMPLEXITY
====================================================================
Let:
    m = nums1.size()
    n = nums2.size()

Time:
    O(m + n) average

Auxiliary space:
    O(m)

The returned answer can additionally contain up to O(min(m, n))
unique values; output space is normally discussed separately.

====================================================================
KEY LESSON
====================================================================
If the problem only asks:
    "Does this value exist?"

and does not require:
    frequency / index / ordering

then an unordered_set is often the natural choice.

Pattern:
    set membership + erase -> unique intersection
*/
