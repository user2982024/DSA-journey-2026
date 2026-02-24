/************************************************************
 *
 *  File: EquilibriumIndex.cpp
 *  Problem: Find Equilibrium Index (GFG)
 *
 *  --------------------------------------------------------
 *  PROBLEM STATEMENT
 *  --------------------------------------------------------
 *  Return the first index i such that:
 *
 *      sum(arr[0 .. i-1]) == sum(arr[i+1 .. n-1])
 *
 *  If no such index exists, return -1.
 *
 *  --------------------------------------------------------
 *  APPROACH
 *  --------------------------------------------------------
 *
 *  Step 1: Compute total sum of array.
 *
 *  Step 2: Traverse array while maintaining leftSum.
 *
 *  At index i:
 *
 *      rightSum = totalSum - leftSum - arr[i]
 *
 *  If leftSum == rightSum → return i.
 *
 *  Then update:
 *
 *      leftSum += arr[i]
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

    int findEquilibrium(vector<int> &arr) {

        int n = arr.size();

        // Edge case: empty array
        if (n == 0)
            return -1;

        long long totalSum = 0;

        // Step 1: Compute total sum
        for (int i = 0; i < n; i++) {
            totalSum += arr[i];
        }

        long long leftSum = 0;

        // Step 2: Traverse array
        for (int i = 0; i < n; i++) {

            // Compute right sum dynamically
            long long rightSum = totalSum - leftSum - arr[i];

            // Check equilibrium condition
            if (leftSum == rightSum) {
                return i;
            }

            // Update left sum for next iteration
            leftSum += arr[i];
        }

        return -1;
    }
};


/************************************************************
 *
 * DRY RUN
 *
 * Example:
 * arr = [1, 3, 5, 2, 2]
 *
 * totalSum = 13
 *
 * i = 0
 * leftSum = 0
 * rightSum = 13 - 0 - 1 = 12
 * not equal
 *
 * i = 1
 * leftSum = 1
 * rightSum = 13 - 1 - 3 = 9
 * not equal
 *
 * i = 2
 * leftSum = 4
 * rightSum = 13 - 4 - 5 = 4
 * equal → return 2
 *
 ************************************************************/