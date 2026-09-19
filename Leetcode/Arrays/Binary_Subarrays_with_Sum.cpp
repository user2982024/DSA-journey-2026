/*****************************************************************************************
*
*  File Name     : BinarySubarraysWithSum.cpp
*  Problem       : Binary Subarrays With Sum
*  Platform      : LeetCode
*
*  ----------------------------------------------------------------------------------------
*  PROBLEM STATEMENT
*
*  Given a binary array nums (containing only 0 and 1) and an integer goal,
*  return the number of non-empty subarrays with sum equal to goal.
*
*  Example:
*      Input  : nums = [1,0,1,0,1], goal = 2
*      Output : 4
*
*  ----------------------------------------------------------------------------------------
*  WHY BRUTE FORCE IS BAD?
*
*  Brute force:
*      - Fix starting index i
*      - Expand j
*      - Calculate sum each time
*
*  Time Complexity = O(n²)
*  Not acceptable for n up to 3 * 10^4.
*
*  ----------------------------------------------------------------------------------------
*  OPTIMAL APPROACH: PREFIX SUM + HASHMAP (FREQUENCY MAP)
*
*  MATHEMATICAL DERIVATION
*
*      Let prefix[i] = sum of elements from index 0 to i.
*
*      Sum of subarray from l to r:
*
*          sum(l, r) = prefix[r] - prefix[l - 1]
*
*      We want:
*
*          prefix[r] - prefix[l - 1] = goal
*
*      Rearranging:
*
*          prefix[l - 1] = prefix[r] - goal
*
*  So at every index r:
*
*      If there exists a previous prefix equal to (prefix - goal),
*      then we found valid subarray(s).
*
*      Number of such subarrays =
*          frequency of (prefix - goal)
*
******************************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int numSubarraysWithSum(vector<int>& nums, int goal) {

        int n = nums.size();

        // HashMap to store frequency of prefix sums
        unordered_map<int, int> freqMap;

        int prefix = 0;   // Running prefix sum
        int count  = 0;   // Number of valid subarrays

        /*************************************************************************
         IMPORTANT INITIALIZATION
         ------------------------------------------------------------------------
         We assume prefix sum = 0 occurred once before the array starts.
         This handles subarrays that start from index 0.
        *************************************************************************/
        freqMap[0] = 1;

        for (int i = 0; i < n; i++) {

            // Step 1: Update running prefix sum
            prefix += nums[i];

            /*********************************************************************
             Step 2: Check if there exists a previous prefix such that:
             
                 prefix - previous_prefix = goal
             
             =>  previous_prefix = prefix - goal
            *********************************************************************/
            if (freqMap.find(prefix - goal) != freqMap.end()) {
                count += freqMap[prefix - goal];
            }

            // Step 3: Store current prefix for future use
            freqMap[prefix]++;
        }

        return count;
    }
};