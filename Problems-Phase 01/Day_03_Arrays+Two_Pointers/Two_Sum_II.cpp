/*
===========================================================
DSA Journey 2026 - Phase 01
Day 03 - Two Pointers
Problem 01: Two Sum II - Input Array Is Sorted
LeetCode 167
===========================================================

Problem Link:
https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

-----------------------------------------------------------
PROBLEM STATEMENT
-----------------------------------------------------------

Given a 1-indexed array of integers `numbers` that is already
sorted in non-decreasing order, find two numbers such that
they add up to a specific target number.

Return the indices of the two numbers as an array [index1, index2].

The indices must be 1-indexed.

Constraints:
- Each input has exactly one solution.
- The same element cannot be used twice.
- The solution must use O(1) extra space.

Example:

Input:
numbers = [2, 7, 11, 15]
target = 9

Output:
[1, 2]

Explanation:
numbers[0] + numbers[1] = 2 + 7 = 9


===========================================================
APPROACH 1 - BRUTE FORCE
===========================================================

The simplest approach is to check every possible pair.

For every element:
    Check it with every element after it.

Example:

[2, 7, 11, 15]

Check:
2 + 7
2 + 11
2 + 15
7 + 11
7 + 15
11 + 15

As soon as we find the target sum, return the indices.

Time Complexity:
O(n^2)

Space Complexity:
O(1)

Although this works, it does not take advantage of the fact
that the array is sorted.


===========================================================
APPROACH 2 - TWO POINTERS
===========================================================

Because the array is sorted, we can use two pointers.

One pointer starts from the beginning:

    start = 0

The other starts from the end:

    end = n - 1


Example:

numbers = [2, 7, 11, 15]
target = 9

             start       end
                ↓          ↓
              [2, 7, 11, 15]


Calculate:

numbers[start] + numbers[end]

Initially:

2 + 15 = 17


The target is 9.

17 > 9

Therefore, we need a SMALLER sum.

Because the array is sorted, moving `start` forward would
increase the first number, making the sum even larger.

So the only useful movement is:

    end--


Now:

2 + 11 = 13

Still greater than 9.

Again:

    end--


Now:

2 + 7 = 9

We found the answer.


-----------------------------------------------------------
IMPORTANT TWO-POINTER RULE
-----------------------------------------------------------

If:

    numbers[start] + numbers[end] > target

then:

    end--

Why?

Because the array is sorted, and moving `end` backward
decreases the value.

-----------------------------------------------------------

If:

    numbers[start] + numbers[end] < target

then:

    start++

Why?

Because the array is sorted, and moving `start` forward
increases the value.

-----------------------------------------------------------

If:

    numbers[start] + numbers[end] == target

then:

    return the two indices.


===========================================================
WHY DOES THIS WORK?
===========================================================

The important observation is the sorted order.

Suppose:

    numbers[start] + numbers[end] > target

Since `numbers[end]` is currently the largest available
value on the right side, keeping it and moving `start`
forward would only make the sum larger.

Therefore, `end` must move backward.

Similarly:

    numbers[start] + numbers[end] < target

Moving `end` backward would make the sum even smaller.

Therefore, `start` must move forward.

This allows us to eliminate many impossible pairs without
checking them individually.


===========================================================
DRY RUN
===========================================================

numbers = [2, 7, 11, 15]
target = 9

Initial:

start = 0
end = 3

2 + 15 = 17

17 > 9

Move end:

end = 2


Now:

2 + 11 = 13

13 > 9

Move end:

end = 1


Now:

2 + 7 = 9

9 == 9

Return:

[start + 1, end + 1]

= [1, 2]


The problem uses 1-based indexing, while C++ vectors use
0-based indexing.

Therefore we return:

    start + 1
    end + 1


===========================================================
C++ SOLUTION
===========================================================
*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {

        int n = numbers.size();

        int start = 0;
        int end = n - 1;

        while (start < end) {

            int sum = numbers[start] + numbers[end];

            if (sum == target) {
                return {start + 1, end + 1};
            }

            if (sum > target) {
                end--;
            }
            else {
                start++;
            }
        }

        // The problem guarantees a solution,
        // but return an empty vector as a safe fallback.
        return {};
    }
};


/*
===========================================================
COMPLEXITY ANALYSIS
===========================================================

Time Complexity:
O(n)

Why?

The `start` pointer only moves forward and the `end` pointer
only moves backward.

Neither pointer ever moves backward after moving forward.

Therefore, across the complete execution, the pointers make
at most O(n) total movements.


Space Complexity:
O(1)

Only a few integer variables are used:

    n
    start
    end
    sum

No additional data structure proportional to the input size
is required.


===========================================================
KEY LEARNING
===========================================================

The major lesson from this problem is the Two-Pointer pattern.

When we see:

    1. A sorted array
    2. A pair-related target condition
    3. Need to find two elements

we should immediately consider:

    Left Pointer + Right Pointer


General pattern:

    left = 0
    right = n - 1

    while (left < right):

        if condition is satisfied:
            answer found

        else if current value is too large:
            right--

        else:
            left++


===========================================================
PERSONAL LEARNING / INSIGHT
===========================================================

This problem reinforced an important observation:

If the array is sorted, pointer movement can be decided
based on whether the current sum is greater than or less
than the target.

If:

    current sum > target

move the right pointer backward.

If:

    current sum < target

move the left pointer forward.

This pattern can be reused in many other problems.


===========================================================
FINAL RESULT
===========================================================

Problem:
LeetCode 167 - Two Sum II

Pattern:
Two Pointers

Difficulty:
Medium

Time:
O(n)

Space:
O(1)

Status:
SOLVED

===========================================================
*/