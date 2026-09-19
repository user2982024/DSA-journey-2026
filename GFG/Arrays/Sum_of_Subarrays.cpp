/***************************************************************
 *  File Name   : sum_of_all_subarray_sums.cpp
 *  Author      : Sheikh Abrar (DSA Practice)
 *  Created On  : 22-2-2026-Sunday
 *
 *  Problem     : Sum of All Subarray Sums
 *  Platform    : GeeksforGeeks / General DSA Pattern
 *
 *  ------------------------------------------------------------
 *  Problem Description
 *  ------------------------------------------------------------
 *  Given an array of integers, compute the SUM of the SUMS of
 *  all possible contiguous subarrays.
 *
 *  Example:
 *      arr = [1, 2, 3]
 *
 *      Subarrays:
 *          [1]       -> 1
 *          [1,2]     -> 3
 *          [1,2,3]   -> 6
 *          [2]       -> 2
 *          [2,3]     -> 5
 *          [3]       -> 3
 *
 *      Total = 1 + 3 + 6 + 2 + 5 + 3 = 20
 *
 *  ------------------------------------------------------------
 *  Brute Force Approach (O(N^2))
 *  ------------------------------------------------------------
 *  1. Fix starting index i
 *  2. Expand ending index j ≥ i
 *  3. Compute subarray sum
 *  4. Add to total
 *
 *  Drawback:
 *      Generates all subarrays explicitly
 *      Time complexity = O(N^2)
 *
 *  ------------------------------------------------------------
 *  Optimal Approach (Contribution Technique) — O(N)
 *  ------------------------------------------------------------
 *  Instead of generating subarrays, count how many times each
 *  element appears across ALL subarrays.
 *
 *  Every time an element appears in a subarray, its value is
 *  added once to the total sum.
 *
 *  So for each element:
 *
 *      contribution = value × number_of_subarrays_containing_it
 *
 *  ------------------------------------------------------------
 *  Mathematical Derivation
 *  ------------------------------------------------------------
 *  Consider element at index i.
 *
 *  A subarray that contains index i must:
 *
 *      start index ≤ i
 *      end index   ≥ i
 *
 *  Count choices:
 *
 *      Possible starts = indices [0 ... i]
 *                      = (i + 1) choices
 *
 *      Possible ends   = indices [i ... n-1]
 *                      = (n - i) choices
 *
 *  Total subarrays containing arr[i]:
 *
 *      (i + 1) * (n - i)
 *
 *  Therefore total contribution:
 *
 *      arr[i] * (i + 1) * (n - i)
 *
 *  Sum contributions for all indices.
 *
 *  ------------------------------------------------------------
 *  Key Insight (Very Important)
 *  ------------------------------------------------------------
 *  We do NOT build subarrays.
 *  We count how many times each element participates.
 *
 *  This transforms nested loops → single loop.
 *
 *  ------------------------------------------------------------
 *  Dry Run
 *  ------------------------------------------------------------
 *  arr = [2, 1, 3]
 *  n = 3
 *
 *  i=0 → 2 appears in 3 subarrays → 2*3 = 6
 *  i=1 → 1 appears in 4 subarrays → 1*4 = 4
 *  i=2 → 3 appears in 3 subarrays → 3*3 = 9
 *
 *  Total = 19
 *
 *  ------------------------------------------------------------
 *  Important Edge Cases
 *  ------------------------------------------------------------
 *  1. Negative numbers → valid (count unaffected)
 *  2. Large values → may cause overflow
 *     Use long long for safety
 *
 *  ------------------------------------------------------------
 *  Time Complexity
 *  ------------------------------------------------------------
 *  O(N) — single traversal
 *
 *  ------------------------------------------------------------
 *  Space Complexity
 *  ------------------------------------------------------------
 *  O(1) — constant extra space
 *
 *  ------------------------------------------------------------
 *  Common Mistakes
 *  ------------------------------------------------------------
 *  1. Using int instead of long long (overflow risk)
 *  2. Confusing index count with value count
 *  3. Forgetting multiplication with element value
 *
 ***************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long subarraySum(vector<int>& arr) {

        int n = arr.size();
        long long totalSum = 0;

        for (int i = 0; i < n; i++) {

            long long leftChoices  = i + 1;
            long long rightChoices = n - i;

            long long contribution =
                (long long)arr[i] * leftChoices * rightChoices;

            totalSum += contribution;
        }

        return totalSum;
    }
};


/***************************************************************
 * Optional Local Testing
 ***************************************************************/
/*
int main() {
    Solution obj;
    vector<int> arr = {1, 2, 3};
    cout << obj.subarraySum(arr) << endl;
    return 0;
}
*/