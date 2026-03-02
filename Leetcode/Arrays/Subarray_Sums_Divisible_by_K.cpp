/*****************************************************************************************
*
*  File Name     : SubarraysDivisibleByK.cpp
*  Problem       : Subarrays Divisible by K
*  Platform      : LeetCode / GFG
*
*  ----------------------------------------------------------------------------------------
*  PROBLEM STATEMENT
*
*  Given an integer array nums and an integer k,
*  return the number of non-empty subarrays whose sum is divisible by k.
*
*  Example:
*      Input  : nums = [4,5,0,-2,-3,1], k = 5
*      Output : 7
*
*  ----------------------------------------------------------------------------------------
*  WHY BRUTE FORCE IS BAD?
*
*  Brute force:
*      - Fix start index i
*      - Expand j
*      - Compute sum for each subarray
*
*  Time Complexity = O(n²)
*  Not acceptable for large constraints (n up to 10^5).
*
*  ----------------------------------------------------------------------------------------
*  OPTIMAL APPROACH: PREFIX SUM + HASHMAP (REMAINDER FREQUENCY)
*
*  MATHEMATICAL DERIVATION:
*
*      Let prefix[i] = sum of elements from index 0 to i.
*
*      Sum of subarray from l to r:
*
*          sum(l, r) = prefix[r] - prefix[l - 1]
*
*      We want:
*
*          (prefix[r] - prefix[l - 1]) % k == 0
*
*      This means:
*
*          prefix[r] % k == prefix[l - 1] % k
*
*  Therefore:
*
*      If two prefix sums have the same remainder when divided by k,
*      their difference is divisible by k.
*
*  So at every index:
*
*      remainder = prefix % k
*
*      If this remainder has appeared before,
*      then we found valid subarray(s).
*
*      Number of such subarrays =
*          frequency of this remainder.
*
******************************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int subarraysDivByK(vector<int>& nums, int k) {

        int n = nums.size();

        // Map to store frequency of remainders
        unordered_map<int, int> mp;

        int prefix = 0;   // Running prefix sum
        int count  = 0;   // Number of valid subarrays

        /*************************************************************************
         IMPORTANT INITIALIZATION
         ------------------------------------------------------------------------
         Before array starts:
             prefix = 0
             remainder = 0
         So we assume remainder 0 occurred once.
        *************************************************************************/
        mp[0] = 1;

        for (int i = 0; i < n; i++) {

            // Step 1: Update running prefix sum
            prefix += nums[i];

            // Step 2: Compute remainder
            int remainder = prefix % k;

            // Step 3: Normalize negative remainder (C++ specific issue)
            if (remainder < 0) {
                remainder += k;
            }

            /*********************************************************************
             Step 4: If this remainder appeared before,
                     we found subarray(s) divisible by k.
            *********************************************************************/
            if (mp.find(remainder) != mp.end()) {
                count += mp[remainder];
            }

            // Step 5: Store remainder for future use
            mp[remainder]++;
        }

        return count;
    }
};