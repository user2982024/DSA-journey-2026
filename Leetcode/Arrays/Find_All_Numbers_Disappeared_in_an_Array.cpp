/*****************************************************************************************
 *
 *  Problem: Find All Numbers Disappeared in an Array
 *  Platform: LeetCode
 *
 *  ---------------------------------------------------------------------------------------
 *  Problem Statement:
 *
 *  Given an integer array nums of size n where:
 *      - Each element is in the range [1, n]
 *      - Some elements appear once or twice
 *      - Some elements are missing
 *
 *  Return all the integers in the range [1, n] that do NOT appear in nums.
 *
 *  ---------------------------------------------------------------------------------------
 *  Example:
 *
 *      Input:  nums = [4,3,2,7,8,2,3,1]
 *      Output: [5,6]
 *
 *      Explanation:
 *      Numbers from 1 to 8 should appear.
 *      Missing numbers are 5 and 6.
 *
 *  ---------------------------------------------------------------------------------------
 *  Constraints:
 *
 *      - Must run in O(n) time
 *      - Must use O(1) extra space (excluding output array)
 *      - Allowed to modify input array
 *
 *  ---------------------------------------------------------------------------------------
 *  Core Observations:
 *
 *  1. Array size = n
 *  2. Values range from 1 to n
 *
 *  This means every value can be mapped to a unique index:
 *
 *      Value 1 -> index 0
 *      Value 2 -> index 1
 *      Value 3 -> index 2
 *      ...
 *      Value x -> index (x - 1)
 *
 *  Therefore, the array itself can be used to track presence of numbers.
 *
 *  ---------------------------------------------------------------------------------------
 *  Technique Used: In-place Negative Marking (Index Marking / In-place Hashing)
 *
 *  Idea:
 *      Use the sign of elements to indicate whether a number has appeared.
 *
 *      If number x appears -> mark index (x - 1) negative.
 *
 *      After marking:
 *          index i positive  -> number (i + 1) missing
 *          index i negative  -> number (i + 1) present
 *
 *  ---------------------------------------------------------------------------------------
 *  Algorithm Steps:
 *
 *  STEP 1 — Mark Presence
 *      For each element nums[i]:
 *          value = abs(nums[i])         (because value may already be negative)
 *          index = value - 1            (convert number to index)
 *
 *          If nums[index] is positive:
 *              make it negative
 *
 *          If already negative:
 *              do nothing (duplicate occurrence)
 *
 *
 *  STEP 2 — Find Missing Numbers
 *      Traverse array again.
 *      If nums[i] is positive:
 *          number (i + 1) never appeared.
 *
 *  ---------------------------------------------------------------------------------------
 *  Why use abs() ?
 *
 *      Because elements become negative during marking.
 *      But we still need original value for index mapping.
 *
 *      abs() restores original number.
 *
 *
 *  Why check nums[index] > 0 ?
 *
 *      To avoid flipping sign twice.
 *
 *      Without this check:
 *          duplicate values would flip sign back to positive
 *          marking would break
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Dry Run Example:
 *
 *      nums = [4,3,2,7,8,2,3,1]
 *
 *      After marking:
 *      [-4,-3,-2,-7,8,2,-3,-1]
 *
 *      Positive indices:
 *          index 4 -> number 5 missing
 *          index 5 -> number 6 missing
 *
 *      Result = [5,6]
 *
 *  ---------------------------------------------------------------------------------------
 *  Time Complexity:
 *
 *      First pass  -> O(n)
 *      Second pass -> O(n)
 *      Total       -> O(n)
 *
 *
 *  Auxiliary Space Complexity:
 *
 *      No extra data structures used.
 *      Only result vector (not counted in auxiliary space).
 *
 *      => O(1) auxiliary space
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Edge Cases Handled:
 *
 *      - No missing numbers
 *      - All numbers identical
 *      - Single element array
 *      - Multiple duplicates
 *
 *****************************************************************************************/

#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {

        int n = nums.size();
        vector<int> result;   // stores missing numbers (output container)

        /*------------------------------------------------------------
            STEP 1 — MARK PRESENCE USING NEGATIVE SIGN
        -------------------------------------------------------------*/
        for (int i = 0; i < n; i++) {

            // Get original value (may already be negative)
            int value = abs(nums[i]);

            // Convert value to index (1-based -> 0-based)
            int index = value - 1;

            // Mark as visited if not already marked
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }

        /*------------------------------------------------------------
            STEP 2 — COLLECT MISSING NUMBERS
        -------------------------------------------------------------*/
        for (int i = 0; i < n; i++) {

            // If still positive -> never visited
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }

        return result;
    }
};