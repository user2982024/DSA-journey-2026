/*****************************************************************************************
*
*  File Name     : SubarraySumEqualsK.cpp
*  Problem       : Subarray Sum Equals K
*  Platform      : LeetCode / GFG
*  Approach      : Prefix Sum + HashMap (Frequency Map)
*
*  ----------------------------------------------------------------------------------------
*  PROBLEM STATEMENT
*
*  Given an integer array nums and an integer k,
*  return the total number of continuous subarrays whose sum equals k.
*
*  Example:
*      Input  : nums = [1, 2, 1, 2, 1], k = 3
*      Output : 4
*
*  ----------------------------------------------------------------------------------------
*  WHY BRUTE FORCE FAILS?
*
*  Brute force approach:
*      - Fix starting index i
*      - Expand ending index j
*      - Compute sum for every subarray
*
*  Time Complexity = O(n²)
*
*  For n up to 10^5, O(n²) is too slow.
*
*  ----------------------------------------------------------------------------------------
*  OPTIMAL APPROACH (O(n))
*
*  KEY MATHEMATICAL IDEA:
*
*      Let prefix[i] = sum of elements from index 0 to i.
*
*      Sum of subarray from index l to r:
*
*          sum(l, r) = prefix[r] - prefix[l - 1]
*
*      We want:
*
*          prefix[r] - prefix[l - 1] = k
*
*      Rearranging:
*
*          prefix[l - 1] = prefix[r] - k
*
*  So at every index r:
*
*      If there exists a previous prefix equal to (current_prefix - k),
*      then we found a valid subarray.
*
*  Therefore:
*
*      count += frequency of (prefix - k)
*
*  ----------------------------------------------------------------------------------------
*  WHY DO WE INSERT freqMap[0] = 1 ?
*
*  Because before the array starts:
*
*      prefix = 0 occurred once.
*
*  This allows us to count subarrays starting from index 0.
*
*  Example:
*      nums = [3], k = 3
*
*      prefix = 3
*      prefix - k = 0
*
*      If freqMap[0] = 1, we correctly count this subarray.
*
******************************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int subarraySum(vector<int>& nums, int k) {

        int n = nums.size();

        // Stores frequency of prefix sums encountered so far
        unordered_map<int, int> freqMap;

        int prefixSum = 0;   // Running cumulative sum
        int count = 0;       // Number of valid subarrays

        // VERY IMPORTANT:
        // Prefix sum 0 has occurred once before array starts
        freqMap[0] = 1;

        for (int i = 0; i < n; i++) {

            // Step 1: Update running prefix sum
            prefixSum += nums[i];

            // Step 2: Check if there exists a prefix such that:
            //         prefixSum - previousPrefix = k
            //   =>    previousPrefix = prefixSum - k

            if (freqMap.find(prefixSum - k) != freqMap.end()) {
                count += freqMap[prefixSum - k];
            }

            // Step 3: Store current prefix sum for future use
            freqMap[prefixSum]++;
        }

        return count;
    }
};

/*****************************************************************************************
*
*  DRY RUN EXAMPLE
*
*  nums = [1, 2, 1, 2, 1]
*  k = 3
*
*  Initial:
*      prefixSum = 0
*      count = 0
*      freqMap = {0:1}
*
*  -----------------------------------------------------
*  i = 0, value = 1
*      prefixSum = 1
*      prefixSum - k = -2 → not found
*      freqMap = {0:1, 1:1}
*
*  -----------------------------------------------------
*  i = 1, value = 2
*      prefixSum = 3
*      prefixSum - k = 0 → found (1 time)
*      count = 1
*      freqMap = {0:1, 1:1, 3:1}
*
*  -----------------------------------------------------
*  i = 2, value = 1
*      prefixSum = 4
*      prefixSum - k = 1 → found (1 time)
*      count = 2
*      freqMap = {0:1, 1:1, 3:1, 4:1}
*
*  -----------------------------------------------------
*  i = 3, value = 2
*      prefixSum = 6
*      prefixSum - k = 3 → found (1 time)
*      count = 3
*      freqMap = {0:1, 1:1, 3:1, 4:1, 6:1}
*
*  -----------------------------------------------------
*  i = 4, value = 1
*      prefixSum = 7
*      prefixSum - k = 4 → found (1 time)
*      count = 4
*
*  Final Answer = 4
*
******************************************************************************************/

/*****************************************************************************************
*
*  TIME COMPLEXITY
*      O(n)
*      Each element processed once.
*      HashMap lookup is O(1) average.
*
*  SPACE COMPLEXITY
*      O(n)
*      In worst case, all prefix sums are unique.
*
******************************************************************************************/

/*****************************************************************************************
*
*  IMPORTANT EDGE CASES
*
*  1) Negative numbers present
*     This solution still works.
*
*  2) k = 0
*     Works perfectly because we check prefix - 0.
*
*  3) Large input
*     If constraints are large, consider using long long for prefixSum.
*
******************************************************************************************/

/*****************************************************************************************
*
*  COMMON MISTAKES
*
*  ❌ Forgetting freqMap[0] = 1
*  ❌ Updating freqMap before checking (wrong order)
*  ❌ Using sliding window when negatives exist
*  ❌ Not using long long when sum can overflow
*
******************************************************************************************/