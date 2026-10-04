/*
    ============================================================
    LeetCode 11 - Container With Most Water
    ============================================================

    Topic:
    Arrays + Two Pointers

    Difficulty:
    Medium

    ------------------------------------------------------------
    Problem:
    ------------------------------------------------------------
    You are given an integer array `height` where height[i]
    represents the height of a vertical line at position i.

    Choose two lines such that, together with the x-axis,
    they form a container that holds the most water.

    Return the maximum amount of water the container can store.

    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    Input:
    height = [1,8,6,2,5,4,8,3,7]

    Output:
    49

    Explanation:
    The lines at indices 1 and 8 have heights 8 and 7.

    Width  = 8 - 1 = 7
    Height = min(8, 7) = 7

    Area = 7 * 7 = 49

    ------------------------------------------------------------
    Approach:
    ------------------------------------------------------------

    We use the Two Pointer technique.

    Start with:

        left  = 0
        right = n - 1

    At every step:

        width = right - left

        usableHeight = min(height[left], height[right])

        currentArea = usableHeight * width

    Then update the maximum area.

    ------------------------------------------------------------
    Why do we move the shorter pointer?
    ------------------------------------------------------------

    The amount of water is limited by the shorter line.

        Area = min(leftHeight, rightHeight) * width

    Suppose:

        leftHeight < rightHeight

    The left line is the limiting factor.

    If we move the right pointer:

        - Width decreases
        - The limiting height cannot increase

    Therefore, moving the taller pointer cannot give us a
    better container.

    Instead, we move the shorter pointer:

        left++

    The same logic applies when the right line is shorter.

    If both heights are equal, we can move both pointers.

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

    This problem demonstrates an important Two Pointer pattern:

        1. Start pointers at both ends.
        2. Calculate the current result.
        3. Identify the limiting side.
        4. Move the pointer that limits the result.
        5. Continue until the pointers meet.

    ============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int maxArea(vector<int>& height) {

        int left = 0;
        int right = height.size() - 1;

        int maxArea = 0;

        while (left < right) {

            // Height of the container is limited by
            // the shorter of the two lines.
            int currentHeight = min(height[left], height[right]);

            // Distance between the two lines.
            int width = right - left;

            // Calculate current container area.
            int currentArea = currentHeight * width;

            // Store the maximum area found so far.
            maxArea = max(maxArea, currentArea);

            // Move the pointer representing the shorter line.
            if (height[left] < height[right]) {
                left++;
            }
            else if (height[left] > height[right]) {
                right--;
            }
            else {
                // Both heights are equal.
                left++;
                right--;
            }
        }

        return maxArea;
    }
};