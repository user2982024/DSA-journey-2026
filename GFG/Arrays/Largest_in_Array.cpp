/*****************************************************************************************
 *
 *  Problem: Find the Largest Element in an Array
 *  Platform: GeeksforGeeks / Basic Array Interview Problem
 *
 *  ---------------------------------------------------------------------------------------
 *  Problem Statement:
 *
 *  Given an array of integers arr of size n, return the largest element present in
 *  the array.
 *
 *  The array may contain:
 *      - positive numbers
 *      - negative numbers
 *      - zero
 *
 *  We must scan the array and determine the maximum value.
 *
 *  ---------------------------------------------------------------------------------------
 *  Example:
 *
 *      Input:  arr = [10, 5, 20, 8]
 *      Output: 20
 *
 *      Explanation:
 *      20 is the largest element in the array.
 *
 *  ---------------------------------------------------------------------------------------
 *  Constraints:
 *
 *      1 <= n <= large
 *      Array may contain negative values
 *
 *  ---------------------------------------------------------------------------------------
 *  Core Idea:
 *
 *  We need to find the maximum element among all values.
 *
 *  Strategy:
 *      Maintain a variable that stores the largest value seen so far.
 *      Traverse the array and update this variable whenever a bigger value appears.
 *
 *  ---------------------------------------------------------------------------------------
 *  Why initialize with INT_MIN ?
 *
 *      The array may contain negative numbers.
 *
 *      If we initialize with 0, it would fail for arrays like:
 *          [-5, -2, -10]
 *
 *      So we initialize with the smallest possible integer:
 *          INT_MIN
 *
 *      This ensures every array value can be compared correctly.
 *
 *  ---------------------------------------------------------------------------------------
 *  Algorithm Steps:
 *
 *  1. Initialize:
 *         largest_value = INT_MIN
 *
 *  2. Traverse array from index 0 to n-1:
 *         if arr[i] > largest_value:
 *             update largest_value
 *
 *  3. Return largest_value
 *
 *  ---------------------------------------------------------------------------------------
 *  Dry Run:
 *
 *      arr = [3, 7, 2, 9, 5]
 *
 *      start largest = -∞
 *
 *      i=0 → 3 > -∞ → largest = 3
 *      i=1 → 7 > 3  → largest = 7
 *      i=2 → 2 < 7  → no change
 *      i=3 → 9 > 7  → largest = 9
 *      i=4 → 5 < 9  → no change
 *
 *      Answer = 9
 *
 *  ---------------------------------------------------------------------------------------
 *  Time Complexity:
 *
 *      We scan each element once.
 *
 *      T(n) = O(n)
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Space Complexity:
 *
 *      Only one variable used.
 *
 *      Auxiliary space = O(1)
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Edge Cases Handled:
 *
 *      ✔ Single element array
 *      ✔ All elements negative
 *      ✔ All elements same
 *      ✔ Very large or very small values
 *
 *
 *  ---------------------------------------------------------------------------------------
 *  Pattern Category:
 *
 *      Linear scan / running maximum tracking
 *
 *      This is a foundational pattern used in:
 *          - finding minimum element
 *          - stock problems
 *          - Kadane’s algorithm
 *          - greedy algorithms
 *
 *****************************************************************************************/

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:

    int largest(vector<int> &arr) {

        int n = arr.size();

        int largest_value = INT_MIN;   // stores maximum seen so far

        for (int i = 0; i < n; i++) {
            if (arr[i] > largest_value) {
                largest_value = arr[i];
            }
        }

        return largest_value;
    }
};