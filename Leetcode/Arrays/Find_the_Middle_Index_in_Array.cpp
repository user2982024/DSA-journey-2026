/************************************************************
 *
 *  File: FindMiddleIndex.cpp
 *  Problem: LeetCode 1991 - Find the Middle Index
 *
 *  --------------------------------------------------------
 *  PROBLEM SUMMARY
 *  --------------------------------------------------------
 *  Return the leftmost index i such that:
 *
 *      sum(nums[0 .. i-1]) == sum(nums[i+1 .. n-1])
 *
 *  If no such index exists, return -1.
 *
 *  --------------------------------------------------------
 *  APPROACH
 *  --------------------------------------------------------
 *  1. Compute total sum of array.
 *  2. Maintain a running leftSum.
 *  3. For each index i:
 *
 *         rightSum = totalSum - leftSum - nums[i]
 *
 *     If leftSum == rightSum → return i.
 *
 *  --------------------------------------------------------
 *  TIME COMPLEXITY
 *  --------------------------------------------------------
 *  O(n)
 *
 *  --------------------------------------------------------
 *  SPACE COMPLEXITY
 *  --------------------------------------------------------
 *  O(1)
 *
 ************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    int findMiddleIndex(vector<int>& nums) {

        int n = nums.size();

        // Edge case: empty array
        if (n == 0)
            return -1;

        long long totalSum = 0;

        // Step 1: Compute total sum
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
        }

        long long leftSum = 0;

        // Step 2: Traverse and check equilibrium
        for (int i = 0; i < n; i++) {

            // Compute right sum dynamically
            long long rightSum = totalSum - leftSum - nums[i];

            if (leftSum == rightSum) {
                return i;
            }

            leftSum += nums[i];
        }

        return -1;
    }
};


/************************************************************
 *
 * DRY RUN EXAMPLE
 *
 * nums = [2, 3, -1, 8, 4]
 *
 * totalSum = 16
 *
 * i = 0
 * leftSum = 0
 * rightSum = 16 - 0 - 2 = 14
 *
 * i = 1
 * leftSum = 2
 * rightSum = 16 - 2 - 3 = 11
 *
 * i = 2
 * leftSum = 5
 * rightSum = 16 - 5 - (-1) = 12
 *
 * i = 3
 * leftSum = 4
 * rightSum = 16 - 4 - 8 = 4
 * leftSum == rightSum → return 3
 *
 ************************************************************/