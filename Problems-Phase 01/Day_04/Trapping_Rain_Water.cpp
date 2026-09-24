/*
    ============================================================
    LeetCode 42 - Trapping Rain Water
    ============================================================

    Topic:
    Arrays + Two Pointers

    Difficulty:
    Hard

    ------------------------------------------------------------
    Problem:
    ------------------------------------------------------------
    Given an array `height` where height[i] represents the
    height of a vertical bar, calculate how much rainwater
    can be trapped after raining.

    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Input:
    height = [0,1,0,2,1,0,1,3,2,1,2,1]

    Output:
    6

    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    For any position i, the amount of trapped water is:

        water[i] = min(leftMax, rightMax) - height[i]

    if the result is positive.

    We could calculate leftMax and rightMax for every position
    using extra arrays, but that would require O(n) space.

    Instead, we use TWO POINTERS and maintain:

        leftMax
        rightMax

    ------------------------------------------------------------
    Two Pointer Approach:
    ------------------------------------------------------------

        left  = 0
        right = n - 1

        leftMax  = 0
        rightMax = 0

    We compare leftMax and rightMax.

    If:

        leftMax <= rightMax

    then the left side is the limiting boundary.

    Therefore, we process the left position.

    Otherwise:

        rightMax < leftMax

    so the right side is the limiting boundary and we process
    the right position.

    ------------------------------------------------------------
    Why can we process one side safely?
    ------------------------------------------------------------

    Suppose:

        leftMax <= rightMax

    We already know that the right side has a boundary at least
    as high as leftMax.

    Therefore, for the current left position, the water level
    is determined by leftMax.

        trapped water = leftMax - height[left]

    if height[left] < leftMax.

    The same logic applies symmetrically to the right side.

    ------------------------------------------------------------
    Important Implementation Detail:
    ------------------------------------------------------------

    When processing the left side:

        left++;

    When processing the right side:

        right--;

    We use IF / ELSE rather than two independent IF statements.

    This guarantees that only ONE side is processed in each
    iteration.

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

    This problem demonstrates a more advanced Two Pointer
    pattern.

    Instead of simply comparing the current values, we maintain
    information about the maximum boundary on both sides.

        leftMax  -> highest wall encountered from the left
        rightMax -> highest wall encountered from the right

    We always process the side whose maximum boundary is
    smaller.

    ============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int trap(vector<int>& height) {

        int n = height.size();

        int left = 0;
        int right = n - 1;

        int leftMax = 0;
        int rightMax = 0;

        int water = 0;

        while (left < right) {

            // Process the side with the smaller maximum boundary.
            if (leftMax <= rightMax) {

                // If the current height is lower than the
                // maximum boundary on the left, water can be trapped.
                if (height[left] < leftMax) {
                    water += leftMax - height[left];
                }
                else {
                    // Current wall becomes the new left maximum.
                    leftMax = height[left];
                }

                left++;
            }

            else {

                // If the current height is lower than the
                // maximum boundary on the right, water can be trapped.
                if (height[right] < rightMax) {
                    water += rightMax - height[right];
                }
                else {
                    // Current wall becomes the new right maximum.
                    rightMax = height[right];
                }

                right--;
            }
        }

        return water;
    }
};