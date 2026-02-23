/*****************************************************************************************
 *
 *  Problem: Max Consecutive Ones
 *  Platform: LeetCode
 *
 *  ---------------------------------------------------------------------------------------
 *  Problem Statement:
 *
 *  Given a binary array nums, return the maximum number of consecutive 1's in the array.
 *
 *  The array contains only:
 *      0 → break in sequence
 *      1 → continuation of sequence
 *
 *  ---------------------------------------------------------------------------------------
 *  Example:
 *
 *      Input:  nums = [1,1,0,1,1,1]
 *      Output: 3
 *
 *      Explanation:
 *      Longest continuous sequence of 1s is [1,1,1] → length = 3
 *
 *  ---------------------------------------------------------------------------------------
 *  Constraints:
 *
 *      1 <= nums.length <= 10^5
 *      nums[i] is either 0 or 1
 *
 *  ---------------------------------------------------------------------------------------
 *  Core Idea:
 *
 *  We need to track the length of the current streak of consecutive 1s.
 *
 *  When we see:
 *      1 → streak continues → increment counter
 *      0 → streak breaks → reset counter to 0
 *
 *  At each step, update the maximum streak seen so far.
 *
 *  ---------------------------------------------------------------------------------------
 *  Key Insight:
 *
 *  This is a "running streak" or "continuous segment tracking" problem.
 *
 *  We do NOT need nested loops.
 *  A single pass is sufficient.
 *
 *  ---------------------------------------------------------------------------------------
 *  Algorithm Steps:
 *
 *  1. Initialize:
 *         current_streak = 0
 *         max_streak = 0
 *
 *  2. Traverse the array from left to right:
 *
 *         If nums[i] == 1:
 *              increase current_streak
 *
 *         If nums[i] == 0:
 *              reset current_streak to 0
 *
 *         Update max_streak
 *
 *  3. Return max_streak
 *
 *  ---------------------------------------------------------------------------------------
 *  Dry Run:
 *
 *      nums = [1,1,0,1,1,1]
 *
 *      i=0 → 1 → curr=1 → max=1
 *      i=1 → 1 → curr=2 → max=2
 *      i=2 → 0 → curr=0 → max=2
 *      i=3 → 1 → curr=1 → max=2
 *      i=4 → 1 → curr=2 → max=2
 *      i=5 → 1 → curr=3 → max=3
 *
 *      Answer = 3
 *
 *  ---------------------------------------------------------------------------------------
 *  Time Complexity:
 *
 *      We scan the array once.
 *
 *      T(n) = O(n)
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Space Complexity:
 *
 *      Only two integer variables used.
 *
 *      Auxiliary space = O(1)
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Edge Cases Handled:
 *
 *      ✔ All zeros → answer = 0
 *      ✔ All ones → answer = array length
 *      ✔ Single element
 *      ✔ Alternating pattern
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Pattern Category:
 *
 *      Running streak / segment counting
 *      Foundation for sliding window problems
 *
 *****************************************************************************************/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

    int findMaxConsecutiveOnes(vector<int>& nums) {

        int n = nums.size();

        int current_streak = 0;   // length of current sequence of 1s
        int max_streak = 0;       // maximum sequence found

        for (int i = 0; i < n; i++) {

            if (nums[i] == 1) {
                // sequence continues
                current_streak++;
            }
            else {
                // sequence breaks
                current_streak = 0;
            }

            // update global maximum
            max_streak = max(max_streak, current_streak);
        }

        return max_streak;
    }
};