
/*
    ============================================================
    Problem: Range Sum Query - Immutable
    Platform: LeetCode
    Problem Number: 303
    Topic: Arrays, Prefix Sum
    Difficulty: Easy
    ============================================================

    PROBLEM STATEMENT
    ------------------------------------------------------------
    Given an integer array nums, handle multiple queries of the
    following type:

        sumRange(left, right)

    Return the sum of the elements of nums between indices left
    and right, inclusive.

    The array does not change after the NumArray object is
    constructed.

    EXAMPLE
    ------------------------------------------------------------
    Input:
        nums = {-2, 0, 3, -5, 2, -1}

        sumRange(0, 2) = 1
        sumRange(2, 5) = -1
        sumRange(0, 5) = -3

    Output:
        {1, -1, -3}

    Explanation:

        Query 1:
            nums[0] + nums[1] + nums[2]
            = -2 + 0 + 3
            = 1

        Query 2:
            nums[2] + nums[3] + nums[4] + nums[5]
            = 3 + (-5) + 2 + (-1)
            = -1

        Query 3:
            nums[0] + nums[1] + nums[2] +
            nums[3] + nums[4] + nums[5]
            = -2 + 0 + 3 + (-5) + 2 + (-1)
            = -3


    ============================================================
    APPROACH: PREFIX SUM
    ============================================================

    The main idea is to precompute the cumulative sum of the
    array once, during construction of the NumArray object.

    We maintain a private vector:

        prefix[i] = nums[0] + nums[1] + ... + nums[i]

    In other words, prefix[i] stores the sum of every element
    from index 0 through index i.


    CONSTRUCTION PHASE
    ------------------------------------------------------------

    1. Initialize currentSum = 0.

    2. Traverse the input array from left to right.

    3. Add each element to currentSum.

    4. Append currentSum to the prefix vector.

    After construction, prefix contains the cumulative sums of
    the original array.


    QUERY PHASE
    ------------------------------------------------------------

    We want to calculate the sum from index left to index right,
    including both endpoints.

    CASE 1: left == 0

        The required range begins at the first element.

        Therefore:

            sumRange(0, right) = prefix[right]


    CASE 2: left > 0

        prefix[right] contains the sum from index 0 through right.

        However, we only want the elements from left through
        right.

        Therefore, subtract the sum of the elements before left:

            sumRange(left, right)
                = prefix[right] - prefix[left - 1]


    WHY PREFIX SUM WORKS
    ------------------------------------------------------------

    Suppose:

        nums   = {2, 4, 1, 5, 3}
        prefix = {2, 6, 7, 12, 15}

    Consider the query:

        sumRange(1, 3)

    The required sum is:

        nums[1] + nums[2] + nums[3]
        = 4 + 1 + 5
        = 10

    Using the prefix array:

        prefix[3] - prefix[0]
        = 12 - 2
        = 10

    Instead of traversing the requested range, we perform a
    single subtraction.


    ============================================================
    C++ IMPLEMENTATION
    ============================================================
*/

#include <iostream>
#include <vector>

using namespace std;

class NumArray {
private:
    // prefix[i] stores the sum of nums[0] through nums[i].
    vector<int> prefix;

public:
    // Constructor: preprocess the array to build prefix sums.
    NumArray(vector<int>& nums) {

        int iterator = 0;
        int n = nums.size();
        int currentSum = 0;

        while (iterator < n) {

            // Add the current element to the cumulative sum.
            currentSum += nums[iterator];

            // Store the prefix sum for the current index.
            prefix.push_back(currentSum);

            // Move to the next element.
            iterator++;
        }
    }

    // Return the sum of nums[left] through nums[right],
    // including both endpoints.
    int sumRange(int left, int right) {

        // If the range starts at index 0, no subtraction
        // is necessary.
        if (left == 0) {
            return prefix[right];
        }

        // Remove the sum of all elements before left.
        return prefix[right] - prefix[left - 1];
    }
};


/*
    ============================================================
    DRY RUN
    ============================================================

    Input:
        nums = {-2, 0, 3, -5, 2, -1}

    ------------------------------------------------------------
    PART 1: CONSTRUCTING THE PREFIX SUM ARRAY
    ------------------------------------------------------------

    Initially:
        currentSum = 0
        prefix = {}


    ITERATION 1:
        nums[0] = -2

        currentSum = 0 + (-2) = -2
        prefix = {-2}


    ITERATION 2:
        nums[1] = 0

        currentSum = -2 + 0 = -2
        prefix = {-2, -2}


    ITERATION 3:
        nums[2] = 3

        currentSum = -2 + 3 = 1
        prefix = {-2, -2, 1}


    ITERATION 4:
        nums[3] = -5

        currentSum = 1 + (-5) = -4
        prefix = {-2, -2, 1, -4}


    ITERATION 5:
        nums[4] = 2

        currentSum = -4 + 2 = -2
        prefix = {-2, -2, 1, -4, -2}


    ITERATION 6:
        nums[5] = -1

        currentSum = -2 + (-1) = -3
        prefix = {-2, -2, 1, -4, -2, -3}


    FINAL PREFIX ARRAY:
        {-2, -2, 1, -4, -2, -3}


    ------------------------------------------------------------
    PART 2: QUERY sumRange(0, 2)
    ------------------------------------------------------------

    left = 0
    right = 2

    Since left == 0:

        return prefix[2]

        return 1

    Answer: 1


    ------------------------------------------------------------
    PART 3: QUERY sumRange(2, 5)
    ------------------------------------------------------------

    left = 2
    right = 5

    Since left != 0:

        return prefix[5] - prefix[1]

        return -3 - (-2)

        return -1

    Answer: -1


    ------------------------------------------------------------
    PART 4: QUERY sumRange(0, 5)
    ------------------------------------------------------------

    left = 0
    right = 5

    Since left == 0:

        return prefix[5]

        return -3

    Answer: -3


    ============================================================
    EDGE CASES
    ============================================================

    CASE 1: Query begins at index 0
    ------------------------------------------------------------
    nums = {1, 2, 3, 4, 5}

    sumRange(0, 2) = 6

    Explanation:
    Return prefix[2] directly.


    CASE 2: Query covers the entire array
    ------------------------------------------------------------
    nums = {1, 2, 3, 4, 5}

    sumRange(0, 4) = 15

    Explanation:
    The last prefix sum represents the sum of the entire array.


    CASE 3: Query contains one element
    ------------------------------------------------------------
    nums = {2, 4, 6, 8}

    sumRange(2, 2) = 6

    Explanation:
    prefix[2] - prefix[1] = 12 - 6 = 6.


    CASE 4: Negative numbers
    ------------------------------------------------------------
    nums = {-2, 0, 3, -5, 2, -1}

    sumRange(2, 5) = -1

    Explanation:
    Prefix sums work with negative numbers as well as positive
    numbers because they rely on addition and subtraction.


    CASE 5: Zero values
    ------------------------------------------------------------
    nums = {0, 0, 0, 0}

    sumRange(1, 3) = 0

    Explanation:
    All prefix sums are zero, so the difference is zero.


    CASE 6: Single-element array
    ------------------------------------------------------------
    nums = {5}

    sumRange(0, 0) = 5

    Explanation:
    The prefix array contains only one element: 5.


    NOTE:
    The LeetCode problem guarantees valid query indices and a
    non-empty input array. An empty array can be constructed,
    but sumRange must not be called with invalid indices.


    ============================================================
    WHERE I GOT STUCK / DEBUGGING NOTES
    ============================================================

    IMPLEMENTATION STATUS
    ------------------------------------------------------------
    My original implementation is correct for the standard
    LeetCode constraints. No logical correction is required.


    1. BUILDING THE PREFIX ARRAY
    ------------------------------------------------------------

    The key statement is:

        currentSum += nums[iterator];

    After processing index i, currentSum represents the sum of
    every element from index 0 through index i.

    We store that sum using:

        prefix.push_back(currentSum);

    This ensures prefix[i] contains the cumulative sum through
    the corresponding original array index.


    2. WHY SUBTRACT prefix[left - 1]?
    ------------------------------------------------------------

    prefix[right] contains all elements from index 0 to right.

    However, the requested range starts at left, so we need to
    remove the contribution of elements from index 0 to left - 1.

    Therefore:

        rangeSum = prefix[right] - prefix[left - 1];


    3. WHY DO WE NEED THE left == 0 CONDITION?
    ------------------------------------------------------------

    If left == 0, then left - 1 equals -1.

    Accessing prefix[-1] would be invalid.

    When the range starts at index 0, the prefix sum already
    contains exactly the elements we need:

        return prefix[right];


    4. WHY IS THE PREFIX ARRAY PRIVATE?
    ------------------------------------------------------------

    The prefix vector is an internal implementation detail of
    the NumArray class.

    Making it private prevents external code from modifying
    the stored prefix sums directly.


    5. WHY PRECOMPUTE THE SUMS?
    ------------------------------------------------------------

    Without prefix sums, each query could require traversing
    the requested range.

    With prefix sums, the constructor performs preprocessing
    once, and each query requires only a constant number of
    operations.


    ============================================================
    COMPLEXITY ANALYSIS
    ============================================================

    Let n be the number of elements in nums and q be the number
    of sumRange queries.


    CONSTRUCTOR TIME COMPLEXITY: O(n)
    ------------------------------------------------------------

    The constructor traverses the input array once.

    Every element contributes to one cumulative sum and one
    prefix vector entry.

    Therefore, preprocessing takes O(n) time.


    sumRange TIME COMPLEXITY: O(1)
    ------------------------------------------------------------

    Each query performs at most one conditional check and one
    subtraction.

    No loop or additional traversal is required.

    Therefore, each query takes O(1) time.

    For q queries, the total query time is O(q).


    TOTAL TIME COMPLEXITY: O(n + q)
    ------------------------------------------------------------

    Preprocessing takes O(n), and answering q queries takes
    O(q) in total.

    Therefore, the overall time complexity is O(n + q).


    AUXILIARY SPACE COMPLEXITY: O(n)
    ------------------------------------------------------------

    The prefix vector stores n cumulative sums.

    Therefore, the additional storage required by the class
    is O(n).


    ============================================================
    KEY LEARNINGS
    ============================================================

    1. Prefix sums allow range-sum queries to be answered in
       constant time after preprocessing.

    2. prefix[i] stores the sum from index 0 through index i.

    3. A range sum can be calculated by subtracting the prefix
       sum before the requested range from the prefix sum at
       the right endpoint.

    4. When left == 0, return prefix[right] directly.

    5. Preprocessing is especially useful when many queries
       are performed on an array that does not change.

    6. Prefix sums are a foundation for more advanced array
       problems, including subarray sums and prefix-sum hashing.

    ============================================================
    END OF SOLUTION
    ============================================================
*/