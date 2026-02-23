/*****************************************************************************************
 *
 *  Problem: Rearrange Array Elements by Sign
 *  Platform: LeetCode 2149
 *
 *  ---------------------------------------------------------------------------------------
 *  Problem Statement:
 *
 *  You are given an integer array nums of EVEN length consisting of an equal number
 *  of positive and negative integers.
 *
 *  Rearrange the array so that:
 *
 *      1. Positive and negative numbers alternate
 *      2. The first element is positive
 *      3. Relative order among positive numbers remains same
 *      4. Relative order among negative numbers remains same
 *
 *  Return the rearranged array.
 *
 *  ---------------------------------------------------------------------------------------
 *  Example:
 *
 *      Input:  nums = [3,1,-2,-5,2,-4]
 *      Output: [3,-2,1,-5,2,-4]
 *
 *      Explanation:
 *      Positive numbers placed at even indices
 *      Negative numbers placed at odd indices
 *
 *  ---------------------------------------------------------------------------------------
 *  IMPORTANT GUARANTEES:
 *
 *      ✔ Number of positives == number of negatives
 *      ✔ Result must start with positive
 *      ✔ Alternating order required
 *
 *  ---------------------------------------------------------------------------------------
 *  APPROACH 1 (Previous Slower Approach):
 *
 *      - Separate positives and negatives into two arrays
 *      - Merge alternately
 *
 *      Time  = O(n)
 *      Space = O(n) extra (two helper arrays + result)
 *
 *  ---------------------------------------------------------------------------------------
 *  APPROACH 2 (Optimized — Used Here):
 *
 *      Direct placement using index parity.
 *
 *      Since result must alternate and counts are equal:
 *
 *          Even indices  → positive numbers
 *          Odd indices   → negative numbers
 *
 *      Traverse original array once and place elements directly.
 *
 *  ---------------------------------------------------------------------------------------
 *  Why result vector must be pre-sized?
 *
 *      We assign values using index:
 *          ans[index] = value
 *
 *      So indices must already exist.
 *
 *      vector<int> ans(n); creates n valid positions.
 *
 *  ---------------------------------------------------------------------------------------
 *  Algorithm Steps:
 *
 *      1. Create result vector of size n
 *      2. posIndex = 0 (even positions)
 *      3. negIndex = 1 (odd positions)
 *
 *      4. Traverse input array:
 *            if positive → place at posIndex, move +2
 *            if negative → place at negIndex, move +2
 *
 *      5. Return result
 *
 *  ---------------------------------------------------------------------------------------
 *  Dry Run:
 *
 *      nums = [3,1,-2,-5,2,-4]
 *
 *      ans = [_,_,_,_,_,_]
 *
 *      3  → ans[0] = 3
 *      1  → ans[2] = 1
 *     -2  → ans[1] = -2
 *     -5  → ans[3] = -5
 *      2  → ans[4] = 2
 *     -4  → ans[5] = -4
 *
 *      Result = [3,-2,1,-5,2,-4]
 *
 *  ---------------------------------------------------------------------------------------
 *  Time Complexity:
 *
 *      Single traversal of array
 *
 *      T(n) = O(n)
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Space Complexity:
 *
 *      Output array of size n required
 *
 *      Auxiliary space = O(n)
 *
 *  ---------------------------------------------------------------------------------------
 *  Edge Cases:
 *
 *      ✔ Already alternating array
 *      ✔ All positives appear first
 *      ✔ All negatives appear first
 *      ✔ Minimum size (n = 2)
 *
 *  ---------------------------------------------------------------------------------------
 *  Pattern Category:
 *
 *      Index placement / parity-based arrangement
 *
 *****************************************************************************************/

#include <vector>
using namespace std;

class Solution {
public:

    vector<int> rearrangeArray(vector<int>& nums) {

        int n = nums.size();

        // Result array must be pre-sized for index assignment
        vector<int> ans(n);

        // Even indices for positives, odd indices for negatives
        int posIndex = 0;
        int negIndex = 1;

        for (int i = 0; i < n; i++) {

            if (nums[i] >= 0) {      // positive element
                ans[posIndex] = nums[i];
                posIndex += 2;
            }
            else {                   // negative element
                ans[negIndex] = nums[i];
                negIndex += 2;
            }
        }

        return ans;
    }
};