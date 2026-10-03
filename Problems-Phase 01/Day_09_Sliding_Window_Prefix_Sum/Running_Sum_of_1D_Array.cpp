
/*
    ============================================================
    Problem: Running Sum of 1d Array
    Platform: LeetCode
    Problem Number: 1480
    Topic: Arrays, Prefix Sum
    Difficulty: Easy
    ============================================================

    PROBLEM STATEMENT
    ------------------------------------------------------------
    Given an array nums, define the running sum of an array as:

        runningSum[i] = nums[0] + nums[1] + ... + nums[i]

    Return the running sum of nums.

    In other words, each element in the resulting array contains
    the sum of all elements from index 0 up to that index.


    EXAMPLE 1
    ------------------------------------------------------------
    Input:
        nums = {1, 2, 3, 4}

    Output:
        {1, 3, 6, 10}

    Explanation:
        runningSum[0] = 1
        runningSum[1] = 1 + 2 = 3
        runningSum[2] = 1 + 2 + 3 = 6
        runningSum[3] = 1 + 2 + 3 + 4 = 10


    EXAMPLE 2
    ------------------------------------------------------------
    Input:
        nums = {1, 1, 1, 1, 1}

    Output:
        {1, 2, 3, 4, 5}

    Explanation:
        Each position contains the cumulative sum of all
        elements up to that position.


    EXAMPLE 3
    ------------------------------------------------------------
    Input:
        nums = {3, 1, 2, 10, 1}

    Output:
        {3, 4, 6, 16, 17}

    Explanation:
        Each element is added to the sum of the preceding
        elements.


    ============================================================
    APPROACH: PREFIX SUM / RUNNING SUM
    ============================================================

    We traverse the input array from left to right and maintain
    a variable called currentSum.

    Variables:

        n           -> Number of elements in nums.
        ans         -> Vector storing the running sums.
        iterator    -> Index used to traverse the input array.
        currentSum  -> Cumulative sum of elements processed so far.

    ALGORITHM
    ------------------------------------------------------------

    1. Calculate the size of the input array.

    2. Initialize an empty vector ans to store the result.

    3. Initialize iterator = 0 and currentSum = 0.

    4. While iterator < n:

       a. Add nums[iterator] to currentSum.

       b. Append currentSum to ans.

       c. Increment iterator to process the next element.

    5. Return ans after processing every element.


    WHY THIS APPROACH WORKS
    ------------------------------------------------------------

    At every iteration, currentSum contains the sum of all
    elements processed so far.

    When the next element is added, currentSum becomes the sum
    from index 0 through the current index.

    Appending currentSum at every iteration therefore produces
    the required running sum array.

    This approach avoids recalculating the sum from index 0 for
    every position.


    ============================================================
    C++ IMPLEMENTATION
    ============================================================
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {

        int n = nums.size();

        // Stores the cumulative sum at each index.
        vector<int> ans;

        // Index used to traverse the input array.
        int iterator = 0;

        // Running total of all processed elements.
        int currentSum = 0;

        while (iterator < n) {

            // Include the current element in the running sum.
            currentSum += nums[iterator];

            // Store the cumulative sum for this index.
            ans.push_back(currentSum);

            // Move to the next element.
            iterator++;
        }

        // Return the complete running sum array.
        return ans;
    }
};


/*
    ============================================================
    DRY RUN
    ============================================================

    Input:
        nums = {1, 2, 3, 4}

    Initial state:
        n = 4
        ans = {}
        iterator = 0
        currentSum = 0


    ITERATION 1
    ------------------------------------------------------------
    Condition:
        iterator < n
        0 < 4 -> true

    Add nums[0] to currentSum:
        currentSum = 0 + 1 = 1

    Append currentSum:
        ans = {1}

    Increment iterator:
        iterator = 1


    ITERATION 2
    ------------------------------------------------------------
    Condition:
        1 < 4 -> true

    Add nums[1] to currentSum:
        currentSum = 1 + 2 = 3

    Append currentSum:
        ans = {1, 3}

    Increment iterator:
        iterator = 2


    ITERATION 3
    ------------------------------------------------------------
    Condition:
        2 < 4 -> true

    Add nums[2] to currentSum:
        currentSum = 3 + 3 = 6

    Append currentSum:
        ans = {1, 3, 6}

    Increment iterator:
        iterator = 3


    ITERATION 4
    ------------------------------------------------------------
    Condition:
        3 < 4 -> true

    Add nums[3] to currentSum:
        currentSum = 6 + 4 = 10

    Append currentSum:
        ans = {1, 3, 6, 10}

    Increment iterator:
        iterator = 4


    LOOP TERMINATION
    ------------------------------------------------------------
    Condition:
        iterator < n
        4 < 4 -> false

    The loop terminates.


    FINAL RESULT
    ------------------------------------------------------------
    Output:
        {1, 3, 6, 10}


    ============================================================
    EDGE CASES
    ============================================================

    CASE 1: Single element
    ------------------------------------------------------------
    Input:
        nums = {5}

    Output:
        {5}

    Explanation:
    The running sum of a single element is the element itself.


    CASE 2: All elements are zero
    ------------------------------------------------------------
    Input:
        nums = {0, 0, 0}

    Output:
        {0, 0, 0}

    Explanation:
    Adding zero does not change the running sum.


    CASE 3: Negative numbers
    ------------------------------------------------------------
    Input:
        nums = {-1, 2, -3, 4}

    Output:
        {-1, 1, -2, 2}

    Explanation:
    The algorithm also works with negative values because it
    simply calculates the cumulative sum.


    CASE 4: Empty array
    ------------------------------------------------------------
    Input:
        nums = {}

    Output:
        {}

    Explanation:
    The loop never executes because iterator = 0 and n = 0.
    The empty result vector is returned.


    CASE 5: Repeated elements
    ------------------------------------------------------------
    Input:
        nums = {2, 2, 2, 2}

    Output:
        {2, 4, 6, 8}

    Explanation:
    Each new element increases the cumulative sum by 2.


    ============================================================
    WHERE I GOT STUCK / DEBUGGING NOTES
    ============================================================

    IMPLEMENTATION STATUS
    ------------------------------------------------------------
    My original implementation is correct for the standard
    problem constraints. No logical correction is required.


    1. MAINTAINING THE RUNNING TOTAL
    ------------------------------------------------------------
    The important idea is to update currentSum incrementally:

        currentSum += nums[iterator];

    There is no need to calculate the sum of all previous
    elements again at every index.

    For example, after processing {1, 2, 3}, currentSum is 6.
    When the next element is 4, simply add 4 to get 10.


    2. STORING THE RESULT
    ------------------------------------------------------------
    After updating currentSum, we append it to ans:

        ans.push_back(currentSum);

    The order matters. First include the current element in
    the sum, then store the result for that index.

    Otherwise, the result could omit the current element.


    3. LOOP TERMINATION
    ------------------------------------------------------------
    The condition:

        while (iterator < n)

    ensures that every valid index from 0 through n - 1 is
    processed exactly once.

    Incrementing iterator after processing each element ensures
    that the loop eventually terminates.


    4. EMPTY ARRAY HANDLING
    ------------------------------------------------------------
    The implementation safely handles an empty vector because
    it initializes currentSum to zero and does not access an
    element unless iterator < n.

    No additional special condition is required.


    ============================================================
    COMPLEXITY ANALYSIS
    ============================================================

    TIME COMPLEXITY: O(n)
    ------------------------------------------------------------

    Let n be the number of elements in nums.

    The while loop processes every element exactly once.

    Each iteration performs:
        1. One addition.
        2. One push_back operation.
        3. One iterator increment.

    Therefore, the time complexity is O(n).


    AUXILIARY SPACE COMPLEXITY: O(n)
    ------------------------------------------------------------

    The ans vector stores n running sums, so the additional
    result storage grows linearly with the input size.

    Therefore, the auxiliary space complexity is O(n), including
    the output vector.

    Excluding the output vector, the algorithm uses O(1)
    auxiliary working space.


    ============================================================
    KEY LEARNINGS
    ============================================================

    1. Running sum is a basic form of the prefix sum technique.

    2. A cumulative variable allows us to calculate each
       successive sum without repeatedly traversing the array.

    3. Every element is processed exactly once, giving O(n)
       time complexity.

    4. push_back() appends each cumulative sum to the result.

    5. The same idea can be extended to prefix sums, range-sum
       queries, subarray problems, and other array algorithms.

    ============================================================
    END OF SOLUTION
    ============================================================
*/