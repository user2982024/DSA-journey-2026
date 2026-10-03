
/*
    ============================================================
    Problem: Minimum Size Subarray Sum
    Platform: LeetCode
    Problem Number: 209
    Topic: Arrays, Sliding Window, Two Pointers
    Difficulty: Medium
    ============================================================

    PROBLEM STATEMENT
    ------------------------------------------------------------
    Given an array of positive integers nums and a positive
    integer target, return the minimal length of a contiguous
    subarray whose sum is greater than or equal to target.

    If no such subarray exists, return 0.

    EXAMPLE 1
    ------------------------------------------------------------
    Input:
        target = 7
        nums = {2, 3, 1, 2, 4, 3}

    Output:
        2

    Explanation:
        The subarray {4, 3} has a sum of 7 and a length of 2.
        No shorter valid subarray exists.

    EXAMPLE 2
    ------------------------------------------------------------
    Input:
        target = 4
        nums = {1, 4, 4}

    Output:
        1

    Explanation:
        The single-element subarray {4} has a sum of 4.

    EXAMPLE 3
    ------------------------------------------------------------
    Input:
        target = 11
        nums = {1, 1, 1, 1, 1, 1, 1, 1}

    Output:
        0

    Explanation:
        The sum of the entire array is less than 11.
        Therefore, no valid subarray exists.


    ============================================================
    APPROACH: SLIDING WINDOW (TWO POINTERS)
    ============================================================

    We maintain a window using two pointers:

        start -> Beginning of the current window.
        end   -> End of the current window.

    Additional variables:

        currentSum -> Sum of the elements in the current window.
        minLength  -> Minimum valid subarray length found so far.

    ALGORITHM
    ------------------------------------------------------------

    1. Initialize start = 0, currentSum = 0, and
       minLength = INT_MAX.

    2. Move the end pointer from left to right through the array.

    3. Add nums[end] to currentSum to expand the window.

    4. While currentSum >= target:

       a. Calculate the current window length:
              currentLength = end - start + 1

       b. Update the minimum length:
              minLength = min(minLength, currentLength)

       c. Remove the leftmost element from the window:
              currentSum -= nums[start]

       d. Move start forward:
              start++

    5. Continue expanding and shrinking the window until end
       reaches the end of the array.

    6. If minLength is still INT_MAX, return 0 because no valid
       subarray was found. Otherwise, return minLength.


    WHY SLIDING WINDOW WORKS
    ------------------------------------------------------------

    The array contains positive integers.

    When we expand the window by moving end forward, the sum
    increases.

    When we shrink the window by moving start forward, the sum
    decreases.

    Once the sum reaches or exceeds the target, we record the
    current length and try to make the window smaller.

    This avoids repeatedly calculating the sum of every possible
    subarray using nested loops.

    IMPORTANT:
    This sliding window approach relies on positive integers.
    For arrays containing negative numbers, this general
    approach does not necessarily work.


    ============================================================
    C++ SOLUTION
    ============================================================
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

        int n = nums.size();

        int start = 0;
        int currentSum = 0;
        int minLength = INT_MAX;

        // Expand the window by moving end forward.
        for (int end = 0; end < n; end++) {

            currentSum += nums[end];

            // Shrink the window while its sum is sufficient.
            while (currentSum >= target) {

                int currentLength = end - start + 1;

                // Update the minimum valid subarray length.
                minLength = min(minLength, currentLength);

                // Remove the leftmost element.
                currentSum -= nums[start];

                // Move the beginning of the window forward.
                start++;
            }
        }

        // Return 0 if no valid subarray was found.
        if (minLength == INT_MAX) {
            return 0;
        }

        return minLength;
    }
};


/*
    ============================================================
    DRY RUN
    ============================================================

    Input:
        target = 7
        nums = {2, 3, 1, 2, 4, 3}

    Initial state:
        start = 0
        currentSum = 0
        minLength = INT_MAX


    STEP 1:
    ------------------------------------------------------------
    Add nums[0] = 2.

    Window: {2}
    Sum: 2

    Since 2 < 7, expand the window.


    STEP 2:
    ------------------------------------------------------------
    Add nums[1] = 3.

    Window: {2, 3}
    Sum: 5

    Since 5 < 7, expand the window.


    STEP 3:
    ------------------------------------------------------------
    Add nums[2] = 1.

    Window: {2, 3, 1}
    Sum: 6

    Since 6 < 7, expand the window.


    STEP 4:
    ------------------------------------------------------------
    Add nums[3] = 2.

    Window: {2, 3, 1, 2}
    Sum: 8

    Since 8 >= 7, the window is valid.

    Current length = 4
    minLength = 4

    Remove nums[start] = 2.

    New window: {3, 1, 2}
    New sum: 6

    The sum is now less than 7, so stop shrinking.


    STEP 5:
    ------------------------------------------------------------
    Add nums[4] = 4.

    Window: {3, 1, 2, 4}
    Sum: 10

    Current length = 4
    minLength = 4

    Remove nums[start] = 3.

    New window: {1, 2, 4}
    New sum: 7

    The window is still valid.

    Current length = 3
    minLength = 3

    Remove nums[start] = 1.

    New window: {2, 4}
    New sum: 6

    The sum is now less than 7, so stop shrinking.


    STEP 6:
    ------------------------------------------------------------
    Add nums[5] = 3.

    Window: {2, 4, 3}
    Sum: 9

    Current length = 3
    minLength = 3

    Remove nums[start] = 2.

    New window: {4, 3}
    New sum: 7

    The window is still valid.

    Current length = 2
    minLength = 2

    Remove nums[start] = 4.

    New window: {3}
    New sum: 3

    The sum is now less than 7, so stop shrinking.


    FINAL RESULT
    ------------------------------------------------------------
    Minimum subarray length = 2

    The answer is 2 because the subarray {4, 3} meets the
    target and has the minimum possible length.


    ============================================================
    EDGE CASES
    ============================================================

    CASE 1: Single element meets the target
    ------------------------------------------------------------
    target = 4
    nums = {4}

    Output: 1

    Explanation:
    One element is sufficient to reach the target.


    CASE 2: Single element exceeds the target
    ------------------------------------------------------------
    target = 5
    nums = {8, 2, 1}

    Output: 1

    Explanation:
    The element 8 alone meets the target.


    CASE 3: Entire array is required
    ------------------------------------------------------------
    target = 7
    nums = {2, 2, 3}

    Output: 3

    Explanation:
    The sum of all three elements is 7.


    CASE 4: No valid subarray exists
    ------------------------------------------------------------
    target = 11
    nums = {1, 1, 1, 1}

    Output: 0

    Explanation:
    The sum of the entire array is less than the target.


    CASE 5: Multiple valid subarrays exist
    ------------------------------------------------------------
    target = 7
    nums = {2, 3, 1, 2, 4, 3}

    Output: 2

    Explanation:
    The subarray {4, 3} is the shortest valid subarray.


    CASE 6: Empty array
    ------------------------------------------------------------
    target = 7
    nums = {}

    Output: 0

    Explanation:
    No subarray exists. The implementation safely handles an
    empty vector because currentSum is initialized to zero.


    ============================================================
    WHERE I GOT STUCK / DEBUGGING NOTES
    ============================================================

    1. INITIALIZING currentSum WITH nums[end]
    ------------------------------------------------------------
    In my original implementation, I used:

        int end = 0;
        int currentSum = nums[end];

    This directly accesses the first element of the array.
    If the array is empty, this access is invalid.

    Improvement:
        int currentSum = 0;

    Add elements to the running sum as the end pointer moves.


    2. INFINITE LOOP IN THE ORIGINAL IMPLEMENTATION
    ------------------------------------------------------------
    My original outer loop was:

        while (end < n)

    Inside it, I had another loop that expanded the window:

        while (currentSum < target)

    When end reached n, I used break to exit the inner loop.

    However, break exits only the innermost loop. It does not
    terminate the outer while loop.

    If currentSum remained smaller than target, the outer loop
    could repeat indefinitely because end was no longer moving.

    Improvement:
    Use a for loop to advance end automatically from 0 to n - 1.


    3. UPDATING minLength AT THE CORRECT TIME
    ------------------------------------------------------------
    Whenever currentSum >= target, the current window is valid.

    Therefore, calculate its length and update minLength before
    removing the leftmost element.

    If the window is not evaluated before shrinking, a smaller
    valid subarray could be missed.


    4. RETURNING THE CORRECT RESULT WHEN NO SUBARRAY EXISTS
    ------------------------------------------------------------
    Initially, minLength is INT_MAX.

    If no window reaches the target, minLength never changes.

    Returning INT_MAX would be incorrect because the problem
    requires returning 0 when no valid subarray exists.

    Improvement:

        if (minLength == INT_MAX) {
            return 0;
        }


    5. WHY currentLength DOES NOT NEED TO BE INITIALIZED
    ------------------------------------------------------------
    In my original solution, currentLength was declared outside
    the loops.

    In the corrected solution, currentLength is declared inside
    the shrinking loop because it is only needed when the current
    window is valid.

    This makes the variable's purpose and scope clearer.


    ============================================================
    COMPLEXITY ANALYSIS
    ============================================================

    TIME COMPLEXITY: O(n)
    ------------------------------------------------------------

    The end pointer traverses the array once, making at most n
    forward movements.

    The start pointer also moves only forward. Across the entire
    algorithm, it can move at most n times.

    Every element is added to currentSum once and removed from
    currentSum at most once.

    Although a nested while loop is used, the inner loop does not
    restart from the beginning of the array. Both pointers move
    monotonically forward.

    Therefore, the total time complexity is O(n).


    AUXILIARY SPACE COMPLEXITY: O(1)
    ------------------------------------------------------------

    The algorithm uses a fixed number of integer variables:

        start
        end
        currentSum
        currentLength
        minLength
        n

    No additional data structure proportional to the input size
    is created.

    Therefore, the auxiliary space complexity is O(1).


    ============================================================
    KEY LEARNINGS
    ============================================================

    1. Sliding Window is useful for contiguous subarray problems
       when the properties of the input allow the window to be
       expanded and contracted predictably.

    2. Positive integers make this particular sliding window
       approach possible because adding an element cannot
       decrease the sum and removing one cannot increase it.

    3. Nested loops do not automatically imply O(n^2) time.
       Analyze how often each pointer moves.

    4. Always check loop termination, pointer progress, and the
       behavior when no valid answer exists.

    5. Update the best answer before shrinking a valid window.

    6. Use INT_MAX as a sentinel when searching for a minimum,
       but handle the case where the sentinel remains unchanged.

    ============================================================
    END OF SOLUTION
    ============================================================
*/