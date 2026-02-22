/***************************************************************
 *  File Name   : running_sum_of_array.cpp
 *  Author      : Sheikh Abrar (DSA Practice)
 *  Created On  : [Update date as needed]
 *
 *  Problem     : Running Sum of 1D Array
 *  Platform    : LeetCode
 *
 *  ------------------------------------------------------------
 *  Problem Description
 *  ------------------------------------------------------------
 *  Given an integer array nums, return the running sum of nums.
 *
 *  Running sum at index i is defined as:
 *
 *      runningSum[i] = nums[0] + nums[1] + ... + nums[i]
 *
 *  In other words, each index stores the cumulative sum of all
 *  elements from the start of the array up to that index.
 *
 *  ------------------------------------------------------------
 *  Example
 *  ------------------------------------------------------------
 *  Input  : nums = [1, 2, 3, 4]
 *  Output : [1, 3, 6, 10]
 *
 *  Explanation:
 *      index 0 → 1
 *      index 1 → 1 + 2 = 3
 *      index 2 → 1 + 2 + 3 = 6
 *      index 3 → 1 + 2 + 3 + 4 = 10
 *
 *  ------------------------------------------------------------
 *  Core Idea / Intuition
 *  ------------------------------------------------------------
 *  We maintain a cumulative sum variable that keeps track of the
 *  sum of elements seen so far.
 *
 *  At each index:
 *      1. Add current element to cumulative sum
 *      2. Store that cumulative sum in result array
 *
 *  This builds prefix sums step by step.
 *
 *  ------------------------------------------------------------
 *  Algorithm
 *  ------------------------------------------------------------
 *  1. Initialize an empty result vector.
 *  2. Initialize sum = 0.
 *  3. Traverse array from left to right.
 *  4. Add nums[i] to sum.
 *  5. Push sum into result.
 *  6. Return result.
 *
 *  ------------------------------------------------------------
 *  Dry Run
 *  ------------------------------------------------------------
 *  nums = [3, 1, 2, 10]
 *
 *  i=0 → sum=3        → result=[3]
 *  i=1 → sum=3+1=4    → result=[3,4]
 *  i=2 → sum=4+2=6    → result=[3,4,6]
 *  i=3 → sum=6+10=16  → result=[3,4,6,16]
 *
 *  ------------------------------------------------------------
 *  Time Complexity
 *  ------------------------------------------------------------
 *  O(N) → Single pass through array
 *
 *  ------------------------------------------------------------
 *  Space Complexity
 *  ------------------------------------------------------------
 *  O(N) → Output array stores running sums
 *
 *  ------------------------------------------------------------
 *  Edge Cases
 *  ------------------------------------------------------------
 *  1. Empty array → return empty vector
 *  2. Single element → return same element
 *  3. Negative numbers → works correctly
 *
 ***************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();

        // Result vector to store running sums
        vector<int> ans;

        // Cumulative sum tracker
        int sum = 0;

        // Traverse array and build running sum
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            ans.push_back(sum);
        }

        return ans;
    }
};


/***************************************************************
 * Optional Testing (Local Testing Only)
 *
 * Uncomment main() if running locally.
 ***************************************************************/
/*
int main() {
    Solution obj;
    vector<int> nums = {1, 2, 3, 4};

    vector<int> result = obj.runningSum(nums);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    return 0;
}
*/