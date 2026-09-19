/***************************************************************
 *  File Name   : pivot_index.cpp
 *  Author      : Sheikh Abrar (DSA Practice)
 *  Created On  : [Update date]
 *
 *  Problem     : Find Pivot Index
 *  Platform    : LeetCode
 *
 *  ------------------------------------------------------------
 *  Problem Description
 *  ------------------------------------------------------------
 *  Given an integer array nums, return the pivot index.
 *
 *  Pivot index is the index where:
 *
 *      sum of elements strictly to the LEFT of index
 *      equals
 *      sum of elements strictly to the RIGHT of index
 *
 *  If multiple pivot indices exist → return the leftmost one.
 *  If no such index exists → return -1.
 *
 *  ------------------------------------------------------------
 *  Example
 *  ------------------------------------------------------------
 *  Input  : nums = [1,7,3,6,5,6]
 *  Output : 3
 *
 *  Explanation:
 *      Left sum  = 1 + 7 + 3 = 11
 *      Right sum = 5 + 6     = 11
 *
 *  ------------------------------------------------------------
 *  Core Intuition
 *  ------------------------------------------------------------
 *  Instead of recalculating left and right sums for every index
 *  (which would be O(N^2)), we optimize using prefix logic.
 *
 *  Strategy:
 *      1. Compute total sum of array.
 *      2. Traverse array while maintaining running left sum.
 *      3. For index i:
 *
 *          rightSum = totalSum - leftSum - nums[i]
 *
 *      4. If leftSum == rightSum → pivot found.
 *      5. Update leftSum and continue.
 *
 *  Key idea:
 *      At index i, totalSum includes everything.
 *      Remove left portion and current element → right portion.
 *
 *  ------------------------------------------------------------
 *  Why This Works
 *  ------------------------------------------------------------
 *  leftSum always stores sum of elements before i.
 *  totalSum - leftSum - nums[i] gives sum after i.
 *
 *  So both sides can be compared in O(1) time per index.
 *
 *  ------------------------------------------------------------
 *  Important Edge Case Insight
 *  ------------------------------------------------------------
 *  Index 0 can be pivot:
 *      left side empty → sum = 0
 *
 *  Last index can be pivot:
 *      right side empty → sum = 0
 *
 *  Empty side is valid and equals zero.
 *
 *  ------------------------------------------------------------
 *  Dry Run
 *  ------------------------------------------------------------
 *  nums = [2,1,-1]
 *
 *  totalSum = 2
 *
 *  i=0:
 *      leftSum = 0
 *      rightSum = 2 - 0 - 2 = 0
 *      pivot found → return 0
 *
 *  ------------------------------------------------------------
 *  Time Complexity
 *  ------------------------------------------------------------
 *  O(N)
 *  One pass to compute total sum
 *  One pass to check pivot
 *
 *  ------------------------------------------------------------
 *  Space Complexity
 *  ------------------------------------------------------------
 *  O(1)
 *  Only constant extra variables used
 *
 *  ------------------------------------------------------------
 *  Common Mistakes (Very Important)
 *  ------------------------------------------------------------
 *  1. Ignoring index 0 or last index as possible pivot
 *  2. Updating leftSum before checking condition
 *  3. Recomputing sums repeatedly (inefficient)
 *
 ***************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {

        int n = nums.size();

        // Step 1: Compute total sum of array
        int totalSum = 0;
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
        }

        // Step 2: Track running left sum
        int leftSum = 0;

        // Step 3: Check each index as pivot
        for (int i = 0; i < n; i++) {

            // Compute right sum excluding current index
            int rightSum = totalSum - leftSum - nums[i];

            if (leftSum == rightSum) {
                return i;
            }

            // Update left sum after checking
            leftSum += nums[i];
        }

        return -1;
    }
};


/***************************************************************
 * Optional Local Testing
 ***************************************************************/
/*
int main() {
    Solution obj;

    vector<int> nums = {1,7,3,6,5,6};
    cout << obj.pivotIndex(nums) << endl;

    return 0;
}
*/