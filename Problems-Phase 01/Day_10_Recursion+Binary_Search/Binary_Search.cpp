
/*
==========================================================
Problem: 704. Binary Search
Platform: LeetCode
Topics: Binary Search, Arrays
Difficulty: Easy
Language: C++
==========================================================

PROBLEM STATEMENT:
Given an array of integers nums sorted in ascending order
and an integer target, return the index of target if it
exists in nums. Otherwise, return -1.

You must write an algorithm with O(log n) runtime
complexity.

Example 1:
Input:
nums = {-1, 0, 3, 5, 9, 12}
target = 9

Output:
4

Explanation:
The target 9 exists at index 4.


Example 2:
Input:
nums = {-1, 0, 3, 5, 9, 12}
target = 2

Output:
-1

Explanation:
The target 2 does not exist in the array.


Example 3:
Input:
nums = {5}
target = 5

Output:
0

Explanation:
The target exists at index 0.

==========================================================
APPROACH: ITERATIVE BINARY SEARCH
==========================================================

Binary search works on a sorted array.

Instead of checking every element one by one, we examine
the middle element and eliminate half of the remaining
search range in every iteration.

ALGORITHM:

1. INITIALIZE POINTERS:
   start = 0
   end = n - 1

   These pointers define the current search range.

2. LOOP CONDITION:
   Continue while start <= end.

   The search range is valid as long as start does not
   exceed end.

3. CALCULATE THE MIDDLE INDEX:
   mid = start + (end - start) / 2

   This calculation avoids the potential integer overflow
   of (start + end) / 2.

4. COMPARE nums[mid] WITH target:

   Case A: nums[mid] == target
       The target has been found.
       Return mid.

   Case B: nums[mid] < target
       Since the array is sorted, the target must be
       to the right of mid, if it exists.
       Set start = mid + 1.

   Case C: nums[mid] > target
       The target must be to the left of mid, if it exists.
       Set end = mid - 1.

5. TARGET NOT FOUND:
   If the loop ends, return -1.

==========================================================
CODE:
==========================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();

        // Initialize the search boundaries
        int start = 0;
        int end = n - 1;

        // Continue while the search range is valid
        while (start <= end) {

            // Calculate the middle index safely
            int mid = start + (end - start) / 2;

            // Case 1: Target found
            if (nums[mid] == target) {
                return mid;
            }

            // Case 2: Target is in the right half
            else if (nums[mid] < target) {
                start = mid + 1;
            }

            // Case 3: Target is in the left half
            else {
                end = mid - 1;
            }
        }

        // Target does not exist in the array
        return -1;
    }
};

/*
==========================================================
DRY RUN 1: TARGET EXISTS
==========================================================

Input:
nums = {-1, 0, 3, 5, 9, 12}
target = 9

Initial state:
start = 0
end   = 5

Array:
Index:  0   1   2   3   4   5
Value: -1   0   3   5   9  12


ITERATION 1:
----------------------------------------------------------

mid = start + (end - start) / 2
mid = 0 + (5 - 0) / 2
mid = 2

nums[mid] = nums[2] = 3

Compare:
3 == 9?  No.
3 < 9?   Yes.

The target must be in the right half.

Update:
start = mid + 1
start = 3

New search range:
Index 3 to Index 5

Array:
{-1, 0, 3, [5, 9, 12]}


ITERATION 2:
----------------------------------------------------------

start = 3
end = 5

mid = 3 + (5 - 3) / 2
mid = 4

nums[mid] = nums[4] = 9

Compare:
9 == 9? Yes.

The target is found.

Return:
4

Final Output:
4


==========================================================
DRY RUN 2: TARGET DOES NOT EXIST
==========================================================

Input:
nums = {-1, 0, 3, 5, 9, 12}
target = 2

Initial state:
start = 0
end = 5


ITERATION 1:
----------------------------------------------------------

mid = 2
nums[mid] = 3

3 == 2? No.
3 < 2?  No.

Therefore, search the left half.

Update:
end = mid - 1
end = 1

New search range:
Index 0 to Index 1


ITERATION 2:
----------------------------------------------------------

start = 0
end = 1

mid = 0 + (1 - 0) / 2
mid = 0

nums[mid] = -1

-1 == 2? No.
-1 < 2?  Yes.

Search the right half.

Update:
start = mid + 1
start = 1


ITERATION 3:
----------------------------------------------------------

start = 1
end = 1

mid = 1 + (1 - 1) / 2
mid = 1

nums[mid] = 0

0 == 2? No.
0 < 2?  Yes.

Update:
start = mid + 1
start = 2


LOOP TERMINATION:
----------------------------------------------------------

start = 2
end = 1

The condition start <= end is false.

The search range is empty.

Return:
-1

Final Output:
-1


==========================================================
EDGE CASES:
==========================================================

1. EMPTY ARRAY:
   nums = {}
   target = 5

   start = 0
   end = -1

   The loop never executes.

   Output: -1


2. SINGLE ELEMENT, TARGET FOUND:
   nums = {5}
   target = 5

   Output: 0


3. SINGLE ELEMENT, TARGET NOT FOUND:
   nums = {5}
   target = 3

   Output: -1


4. TARGET AT THE BEGINNING:
   nums = {1, 3, 5, 7, 9}
   target = 1

   Output: 0


5. TARGET AT THE END:
   nums = {1, 3, 5, 7, 9}
   target = 9

   Output: 4


6. TARGET SMALLER THAN ALL ELEMENTS:
   nums = {10, 20, 30, 40}
   target = 5

   Output: -1


7. TARGET LARGER THAN ALL ELEMENTS:
   nums = {10, 20, 30, 40}
   target = 50

   Output: -1


==========================================================
WHY DO WE USE start <= end?
==========================================================

The search range includes both start and end.

When start == end, exactly one element remains to be
checked, so the loop must still execute.

When start > end, the search range is empty, so the
algorithm stops.

Using start < end would incorrectly skip the final
remaining element when start == end.


==========================================================
WHY DO WE USE mid + 1 AND mid - 1?
==========================================================

If nums[mid] < target:
    The middle element is too small.
    The sorted order guarantees that every element at
    index mid or earlier is also too small.
    Therefore, start = mid + 1.

If nums[mid] > target:
    The middle element is too large.
    Every element at index mid or later is also too large.
    Therefore, end = mid - 1.

The middle element is excluded from the next range
because it has already been checked.


==========================================================
TIME AND SPACE COMPLEXITY:
==========================================================

Time Complexity: O(log n)
- Each iteration eliminates approximately half of the
  remaining search range.
- The number of iterations grows logarithmically.

Auxiliary Space Complexity: O(1)
- Only a fixed number of integer variables are used.
- The algorithm is iterative and does not use recursion.


==========================================================
KEY LEARNINGS:
==========================================================

1. Binary search requires a sorted array.
2. The middle element determines which half to eliminate.
3. start <= end allows the final remaining element to
   be checked.
4. mid = start + (end - start) / 2 avoids potential
   integer overflow from (start + end) / 2.
5. mid + 1 and mid - 1 prevent repeatedly checking
   the same middle element.
6. Return -1 when the target is not found.
7. Binary search takes O(log n) time and O(1) auxiliary
   space in this iterative implementation.

==========================================================
*/