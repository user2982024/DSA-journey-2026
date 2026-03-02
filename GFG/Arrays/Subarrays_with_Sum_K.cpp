/*****************************************************************************************
*
*  File Name     : CountSubarraysWithGivenSum.cpp
*  Problem       : Count Subarrays With Given Sum (k)
*  Platform      : GeeksforGeeks / LeetCode Variant
*
*  ----------------------------------------------------------------------------------------
*  PROBLEM STATEMENT
*
*  Given an integer array arr[] of size N and an integer k,
*  return the total number of continuous subarrays whose sum equals k.
*
*  Example:
*      Input  : arr = [10, 2, -2, -20, 10], k = -10
*      Output : 3
*
*  ----------------------------------------------------------------------------------------
*  WHY BRUTE FORCE IS NOT OPTIMAL?
*
*  Brute Force:
*      For every starting index i:
*          Keep expanding j
*          Compute sum
*
*  Time Complexity = O(n²)
*  Not acceptable for n up to 10^5.
*
*  ----------------------------------------------------------------------------------------
*  OPTIMAL APPROACH: PREFIX SUM + HASHMAP (FREQUENCY MAP)
*
*  MATHEMATICAL DERIVATION:
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
*  So at each index r:
*
*      If there exists a previous prefix equal to (current_prefix - k),
*      then we found valid subarray(s).
*
*      Number of such subarrays =
*          frequency of (current_prefix - k)
*
******************************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int cntSubarrays(vector<int> &arr, int k) {

        int n = arr.size();

        // HashMap to store frequency of prefix sums
        unordered_map<int, int> mp;

        int prefix = 0;   // Running prefix sum
        int count  = 0;   // Number of valid subarrays

        /*************************************************************************
         IMPORTANT INITIALIZATION
         ------------------------------------------------------------------------
         We assume that prefix sum = 0 occurred once before array starts.
         This handles subarrays that start from index 0.
        *************************************************************************/
        mp[0] = 1;

        for (int i = 0; i < n; i++) {

            // Step 1: Update running prefix sum
            prefix += arr[i];

            /*********************************************************************
             Step 2: Check if there exists a previous prefix such that:
             
                 prefix - previous_prefix = k
             
             =>  previous_prefix = prefix - k
            *********************************************************************/

            if (mp.find(prefix - k) != mp.end()) {
                count += mp[prefix - k];
            }

            // Step 3: Store current prefix for future use
            mp[prefix]++;
        }

        return count;
    }
};