
/*
    ============================================================
    Problem: Longest Subarray with Sum K
    Platform: GeeksforGeeks (GFG)
    Topic: Arrays, Prefix Sum, Hashing, Unordered Map
    Difficulty: Medium
    ============================================================

    PROBLEM STATEMENT
    ------------------------------------------------------------
    Given an array arr[] of integers and an integer k, find the
    length of the longest subarray whose sum is equal to k.

    A subarray is a contiguous, non-empty sequence of elements
    from the original array.

    If no subarray has a sum equal to k, return 0.


    EXAMPLE 1
    ------------------------------------------------------------
    Input:
        arr = {10, 5, 2, 7, 1, -10}
        k = 15

    Output:
        4

    Explanation:
        The subarray {5, 2, 7, 1} has a sum of 15 and length 4.
        It is the longest subarray whose sum equals 15.


    EXAMPLE 2
    ------------------------------------------------------------
    Input:
        arr = {-5, 8, -14, 2, 4, 12}
        k = -5

    Output:
        5

    Explanation:
        The subarray {-5, 8, -14, 2, 4} has a sum of -5 and
        length 5.


    EXAMPLE 3
    ------------------------------------------------------------
    Input:
        arr = {1, 2, 3}
        k = 10

    Output:
        0

    Explanation:
        No subarray has a sum equal to 10.


    ============================================================
    APPROACH: PREFIX SUM + HASHING
    ============================================================

    We use a prefix sum and an unordered_map to store the
    earliest index at which each prefix sum appears.

    VARIABLES
    ------------------------------------------------------------

    currentSum:
        The sum of all elements from index 0 through the
        current index i.

    prefixMap:
        Stores prefixMap[prefixSum] = earliest index at which
        that prefix sum occurred.

    maxLength:
        The maximum length of any valid subarray found so far.


    THE MATHEMATICAL IDEA
    ------------------------------------------------------------

    Suppose the prefix sum at index i is:

        currentSum = arr[0] + arr[1] + ... + arr[i]

    We want a subarray ending at index i whose sum is k.

    Let the starting index of that subarray be j + 1.

    Then:

        arr[j + 1] + ... + arr[i] = k

    Using prefix sums:

        currentSum - prefixSum[j] = k

    Rearranging:

        prefixSum[j] = currentSum - k

    Therefore, whenever currentSum - k exists in prefixMap,
    a subarray with sum k exists.

    Its length is:

        i - prefixMap[currentSum - k]


    ALGORITHM
    ------------------------------------------------------------

    1. Create an unordered_map called prefixMap.

    2. Initialize:
           currentSum = 0
           maxLength = 0

    3. Insert:
           prefixMap[0] = -1

       This handles subarrays that start at index 0.

    4. Traverse the array from left to right.

    5. At each index i:

       a. Add arr[i] to currentSum.

       b. Check whether currentSum - k exists in prefixMap.

       c. If it exists, calculate the subarray length:

              currentLength = i - prefixMap[currentSum - k]

          Update maxLength if the new length is larger.

       d. If currentSum has never appeared before, store its
          current index in prefixMap.

    6. Return maxLength.


    WHY WE STORE THE EARLIEST INDEX
    ------------------------------------------------------------

    Suppose the same prefix sum appears at indices 2 and 7.

    If we want the longest possible subarray ending at a later
    index i, using index 2 gives a longer subarray than using
    index 7.

    Therefore, we store a prefix sum only the first time it
    appears. We never overwrite its earliest index.


    WHY PREFIXMAP[0] = -1 IS IMPORTANT
    ------------------------------------------------------------

    Consider:

        arr = {2, 3, 1}
        k = 6

    At index 2:

        currentSum = 6
        currentSum - k = 0

    The prefix sum 0 must be associated with index -1.

    Therefore:

        currentLength = 2 - (-1) = 3

    This correctly identifies the entire array as a valid
    subarray of length 3.


    ============================================================
    C++ IMPLEMENTATION
    ============================================================
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& arr, int k) {

        // Stores each prefix sum's earliest occurrence.
        unordered_map<int, int> prefixMap;

        int n = arr.size();
        int currentSum = 0;
        int maxLength = 0;

        // Handles subarrays that begin at index 0.
        prefixMap[0] = -1;

        for (int i = 0; i < n; i++) {

            // Update the prefix sum.
            currentSum += arr[i];

            // Check whether a subarray ending at i has sum k.
            int requiredSum = currentSum - k;

            if (prefixMap.find(requiredSum) != prefixMap.end()) {

                int currentLength = i - prefixMap[requiredSum];

                maxLength = max(maxLength, currentLength);
            }

            // Store only the earliest index for each prefix sum.
            if (prefixMap.find(currentSum) == prefixMap.end()) {
                prefixMap[currentSum] = i;
            }
        }

        // Return 0 if no valid subarray was found.
        return maxLength;
    }
};


/*
    ============================================================
    DRY RUN
    ============================================================

    Input:
        arr = {10, 5, 2, 7, 1, -10}
        k = 15

    Initially:
        currentSum = 0
        maxLength = 0
        prefixMap = {0: -1}


    ------------------------------------------------------------
    ITERATION 1: i = 0
    ------------------------------------------------------------

    arr[0] = 10

    currentSum = 0 + 10 = 10
    requiredSum = 10 - 15 = -5

    Is -5 in prefixMap?
        No.

    Has prefix sum 10 appeared before?
        No.

    Store:
        prefixMap[10] = 0

    maxLength = 0


    ------------------------------------------------------------
    ITERATION 2: i = 1
    ------------------------------------------------------------

    arr[1] = 5

    currentSum = 10 + 5 = 15
    requiredSum = 15 - 15 = 0

    Is 0 in prefixMap?
        Yes, at index -1.

    currentLength = 1 - (-1) = 2

    maxLength = 2

    Has prefix sum 15 appeared before?
        No.

    Store:
        prefixMap[15] = 1


    ------------------------------------------------------------
    ITERATION 3: i = 2
    ------------------------------------------------------------

    arr[2] = 2

    currentSum = 15 + 2 = 17
    requiredSum = 17 - 15 = 2

    Is 2 in prefixMap?
        No.

    Has prefix sum 17 appeared before?
        No.

    Store:
        prefixMap[17] = 2

    maxLength = 2


    ------------------------------------------------------------
    ITERATION 4: i = 3
    ------------------------------------------------------------

    arr[3] = 7

    currentSum = 17 + 7 = 24
    requiredSum = 24 - 15 = 9

    Is 9 in prefixMap?
        No.

    Has prefix sum 24 appeared before?
        No.

    Store:
        prefixMap[24] = 3

    maxLength = 2


    ------------------------------------------------------------
    ITERATION 5: i = 4
    ------------------------------------------------------------

    arr[4] = 1

    currentSum = 24 + 1 = 25
    requiredSum = 25 - 15 = 10

    Is 10 in prefixMap?
        Yes, at index 0.

    currentLength = 4 - 0 = 4

    maxLength = 4

    Prefix sum 25 has not appeared before.

    Store:
        prefixMap[25] = 4


    ------------------------------------------------------------
    ITERATION 6: i = 5
    ------------------------------------------------------------

    arr[5] = -10

    currentSum = 25 - 10 = 15
    requiredSum = 15 - 15 = 0

    Is 0 in prefixMap?
        Yes, at index -1.

    currentLength = 5 - (-1) = 6

    maxLength = 6

    Prefix sum 15 has appeared before at index 1.
    We do not overwrite its earliest index.


    FINAL RESULT
    ------------------------------------------------------------

    Output:
        6

    Explanation:
        The entire array has a sum of:

            10 + 5 + 2 + 7 + 1 - 10 = 15

        Therefore, the longest valid subarray is the entire
        array, with length 6.


    NOTE:
    The first example's correct answer is 6, not 4, because
    the entire array sums to 15. The subarray of length 4 is
    valid but is not the longest one.


    ============================================================
    EDGE CASES
    ============================================================

    CASE 1: Entire array has sum k
    ------------------------------------------------------------

    Input:
        arr = {1, 2, 3}
        k = 6

    Output:
        3

    Explanation:
    prefixMap[0] = -1 allows the entire array to be counted.


    CASE 2: No valid subarray
    ------------------------------------------------------------

    Input:
        arr = {1, 2, 3}
        k = 10

    Output:
        0

    Explanation:
    No prefix-sum difference equals the target.


    CASE 3: Negative numbers
    ------------------------------------------------------------

    Input:
        arr = {-5, 8, -14, 2, 4, 12}
        k = -5

    Output:
        5

    Explanation:
    Prefix sums support negative values. The longest valid
    subarray is {-5, 8, -14, 2, 4}.


    CASE 4: Zero values
    ------------------------------------------------------------

    Input:
        arr = {0, 0, 0, 0}
        k = 0

    Output:
        4

    Explanation:
    The entire array has sum 0. Keeping the earliest occurrence
    of prefix sum 0 allows the algorithm to find length 4.


    CASE 5: Repeated prefix sums
    ------------------------------------------------------------

    Input:
        arr = {1, -1, 1, -1, 1}
        k = 0

    Output:
        4

    Explanation:
    The subarray {1, -1, 1, -1} has sum 0 and length 4.
    Repeated prefix sums make preserving the earliest index
    especially important.


    CASE 6: Single-element array
    ------------------------------------------------------------

    Input:
        arr = {5}
        k = 5

    Output:
        1

    Explanation:
    The single element forms a valid subarray.


    ============================================================
    WHERE I GOT STUCK / DEBUGGING NOTES
    ============================================================

    IMPLEMENTATION STATUS
    ------------------------------------------------------------

    My original implementation correctly uses prefix sums and
    hashing. No logical correction is required.

    The following concepts are important to understand deeply.


    1. UNDERSTANDING currentSum - k
    ------------------------------------------------------------

    At index i, currentSum represents the sum from index 0
    through index i.

    If an earlier prefix sum equals currentSum - k, subtracting
    that earlier prefix from currentSum leaves exactly k.

    This allows us to identify a valid subarray without
    recalculating the sum of every possible subarray.


    2. WHY prefixMap[0] = -1?
    ------------------------------------------------------------

    It represents a prefix sum of zero before the array begins.

    If currentSum itself equals k, then:

        currentSum - k = 0

    The map returns index -1, so the length becomes:

        i - (-1) = i + 1

    This correctly counts subarrays starting at index 0.


    3. WHY STORE ONLY THE FIRST OCCURRENCE?
    ------------------------------------------------------------

    Consider a prefix sum that appears at multiple indices.

    The earliest index gives the longest possible subarray
    ending at the current position.

    Therefore, we use:

        if (prefixMap.find(currentSum) == prefixMap.end()) {
            prefixMap[currentSum] = i;
        }

    We must not overwrite an earlier index with a later one.


    4. WHY NOT USE A SIMPLE SLIDING WINDOW?
    ------------------------------------------------------------

    A conventional sum-based sliding window relies on the
    sum changing predictably when elements are added or removed.

    With negative numbers, adding an element can decrease the
    sum, and removing an element can increase it.

    Consequently, the usual sliding window approach is not
    generally valid for this problem's full input domain.

    Prefix sums and hashing handle positive, zero, and negative
    integers.


    5. WHY maxLength STARTS AT ZERO
    ------------------------------------------------------------

    Zero is the required answer when no valid subarray exists.

    Every valid non-empty subarray has a positive length, so
    maxLength can be safely updated whenever a valid subarray
    is discovered.


    ============================================================
    COMPLEXITY ANALYSIS
    ============================================================

    TIME COMPLEXITY: O(n) AVERAGE
    ------------------------------------------------------------

    The algorithm traverses the array exactly once.

    At every index, it performs a constant number of operations
    and unordered_map lookups or insertions.

    These operations take O(1) expected time on average.

    Therefore, the expected time complexity is O(n).

    Note:
    unordered_map operations can degrade in the worst case
    because of hash collisions. The theoretical worst-case
    time complexity can be O(n^2).


    AUXILIARY SPACE COMPLEXITY: O(n)
    ------------------------------------------------------------

    In the worst case, every prefix sum can be distinct.

    The unordered_map can therefore store up to n + 1 entries,
    including the initial prefix sum of zero.

    Hence, the auxiliary space complexity is O(n).


    ============================================================
    KEY LEARNINGS
    ============================================================

    1. Prefix sums help transform subarray-sum conditions into
       differences between cumulative sums.

    2. Hashing allows us to find an earlier prefix sum quickly.

    3. Storing the earliest index of each prefix sum is
       essential when the objective is to maximize length.

    4. prefixMap[0] = -1 handles subarrays starting at index 0.

    5. Prefix sum + hashing works with negative integers,
       unlike the conventional sum-based sliding window.

    6. The expected time complexity is O(n), and auxiliary
       space complexity is O(n).

    ============================================================
    END OF SOLUTION
    ============================================================
*/