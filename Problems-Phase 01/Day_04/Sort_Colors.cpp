/*
    ============================================================
    LeetCode 75 - Sort Colors
    ============================================================

    Topic:
    Arrays + Two Pointers + Three Pointers

    Difficulty:
    Medium

    ------------------------------------------------------------
    Problem:
    ------------------------------------------------------------
    Given an array `nums` containing only 0, 1, and 2,
    sort the array in-place so that objects of the same color
    are adjacent.

    Do not use the library sort function.

    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Input:
    nums = [2,0,2,1,1,0]

    Output:
    [0,0,1,1,2,2]

    ------------------------------------------------------------
    Initial Approach:
    ------------------------------------------------------------

    One possible solution is to count the number of:

        0s
        1s
        2s

    and then rewrite the array.

    This solution is:

        Time Complexity:  O(n)
        Space Complexity: O(1)

    However, we can solve the problem using a single traversal
    with the Dutch National Flag algorithm.

    ------------------------------------------------------------
    Dutch National Flag Algorithm:
    ------------------------------------------------------------

    We use three pointers:

        start
        mid
        end

    Their purpose is:

        start -> boundary for 0s
        mid   -> pointer that examines the unknown element
        end   -> boundary for 2s

    ------------------------------------------------------------
    Invariant:
    ------------------------------------------------------------

        [0 ... start-1]
            -> all 0s

        [start ... mid-1]
            -> all 1s

        [mid ... end]
            -> unknown elements

        [end+1 ... n-1]
            -> all 2s

    The `mid` pointer processes the unknown region.

    ------------------------------------------------------------
    Case 1: nums[mid] == 0
    ------------------------------------------------------------

    A 0 belongs to the beginning of the array.

    Swap:

        nums[mid]
        nums[start]

    Then:

        start++
        mid++

    Why increment both?

    Because the 0 has been placed correctly, and the element
    swapped into `mid` came from the already-processed region.

    ------------------------------------------------------------
    Case 2: nums[mid] == 1
    ------------------------------------------------------------

    A 1 belongs in the middle.

    Therefore it is already in the correct region.

    Simply:

        mid++

    ------------------------------------------------------------
    Case 3: nums[mid] == 2
    ------------------------------------------------------------

    A 2 belongs at the end.

    Swap:

        nums[mid]
        nums[end]

    Then:

        end--

    IMPORTANT:
    Do NOT increment `mid`.

    Why?

    Because the element swapped from `end` into `mid` has not
    been examined yet.

    Therefore, `mid` must examine it in the next iteration.

    ------------------------------------------------------------
    Loop Condition:
    ------------------------------------------------------------

        while (mid <= end)

    We continue while there are still unknown elements.

    Once:

        mid > end

    there are no unknown elements remaining.

    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Time Complexity:
        O(n)

    Space Complexity:
        O(1)

    ------------------------------------------------------------
    Key Learning:
    ------------------------------------------------------------

    The most important idea is not simply "use three pointers."

    The important idea is maintaining regions:

        0s | 1s | UNKNOWN | 2s

    The `mid` pointer continuously reduces the UNKNOWN region.

    ============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    void sortColors(vector<int>& nums) {

        int start = 0;
        int mid = 0;
        int end = nums.size() - 1;

        while (mid <= end) {

            // Case 1: Current element is 0.
            if (nums[mid] == 0) {

                swap(nums[start], nums[mid]);

                start++;
                mid++;
            }

            // Case 2: Current element is 1.
            else if (nums[mid] == 1) {

                mid++;
            }

            // Case 3: Current element is 2.
            else {

                swap(nums[mid], nums[end]);

                end--;

                // Do NOT increment mid here.
                // The newly swapped element is still unknown.
            }
        }
    }
};