/*
DAY 1 — ARRAYS + HASHING
Problem 4: Two Sum
Platform: LeetCode
Topic: complement + hash map (value -> index)

SOURCE:
https://leetcode.com/problems/two-sum/

====================================================================
MY APPROACH
====================================================================
Given:
    nums[i] + x = target

Rearrange:
    x = target - nums[i]

So for every current number, I calculate its complement:
    complement = target - nums[i]

Then I ask:
    "Have I already seen this complement?"

To answer that in O(1) average time, I use:
    unordered_map<int, int>

where:
    key   = number
    value = index where I saw that number

Example:
    nums = [2, 7, 11, 15]
    target = 9

At i = 0:
    current = 2
    complement = 9 - 2 = 7
    7 not seen
    store: 2 -> 0

At i = 1:
    current = 7
    complement = 9 - 7 = 2
    2 is present
    map says 2 -> 0
    current index is 1
    return {0, 1}

====================================================================
MY ORIGINAL CODE
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> freqMap;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (freqMap.find(target - nums[i]) != freqMap.end()) {
                return {freqMap[target - nums[i]], i};
            }
            else {
                freqMap[nums[i]] = i;
            }
        }

        // Improved from the original {0, 0} fallback:
        // {0, 0} could look like a valid pair.
        return {};
    }
};

/*
====================================================================
WHY unordered_set DID NOT WORK
====================================================================
unordered_set can answer:
    "Have I seen 2?"

But it cannot tell us:
    "At which index did I see 2?"

Two Sum requires BOTH.

Therefore:
    unordered_set -> existence only
    unordered_map -> number -> index

====================================================================
ALTERNATIVE APPROACHES
====================================================================
1. Brute force:
       Check every pair.
       Time: O(n^2)
       Extra space: O(1)

2. Sorting + two pointers:
       Time: O(n log n)
       But sorting destroys original index positions unless the
       original indices are stored alongside the values.

3. Hash map:
       Time: O(n) average
       Space: O(n)
       Preserves access to original indices naturally.

====================================================================
KEY LESSON
====================================================================
This is the "complement + hash map" pattern:

    target - current = required complement

Then:
    required complement -> lookup in hash map

This same difference/complement idea appears later in
prefix-sum + hash-map problems such as Subarray Sum Equals K.
*/
