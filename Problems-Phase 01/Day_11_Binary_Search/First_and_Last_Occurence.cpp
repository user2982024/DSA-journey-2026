
/*
============================================================
Problem: Find First and Last Position of Element in Sorted Array
Platform: LeetCode
Problem Number: 34
Topic: Binary Search
Difficulty: Medium
============================================================

PROBLEM STATEMENT:
------------------
Given an array of integers nums sorted in non-decreasing order,
find the starting and ending position of a given target value.

If the target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

Example 1:
----------
Input:
nums = [5, 7, 7, 8, 8, 10]
target = 8

Output:
[3, 4]

Explanation:
The first occurrence of 8 is at index 3.
The last occurrence of 8 is at index 4.

Example 2:
----------
Input:
nums = [5, 7, 7, 8, 8, 10]
target = 6

Output:
[-1, -1]

Explanation:
The target 6 does not exist in the array.

Example 3:
----------
Input:
nums = []
target = 0

Output:
[-1, -1]

Explanation:
The array is empty, so the target cannot be found.


============================================================
APPROACH: TWO BINARY SEARCHES
============================================================

The array is sorted, so binary search allows us to find
the target efficiently.

However, the target may appear multiple times.

Therefore, we perform TWO separate binary searches:

1. First Binary Search:
   Find the FIRST occurrence of the target.

2. Second Binary Search:
   Find the LAST occurrence of the target.

We store the results in two variables:

left  = index of the first occurrence
right = index of the last occurrence

Initially, both variables are -1.

If the target is never found, both values remain -1.


============================================================
HOW THE FIRST BINARY SEARCH WORKS
============================================================

We use the following variables:

start = 0
end   = n - 1
left  = -1

While start <= end:

1. Calculate the middle index:
   mid = start + (end - start) / 2

2. Compare nums[mid] with target.

3. If nums[mid] < target:
   The target, if present, must be to the right.
   Therefore:
   start = mid + 1

4. If nums[mid] > target:
   The target, if present, must be to the left.
   Therefore:
   end = mid - 1

5. If nums[mid] == target:
   We have found an occurrence, but it might not be
   the FIRST occurrence.

   Therefore:
   left = mid

   We continue searching on the left side:
   end = mid - 1

IMPORTANT:
When we find the target, we do not immediately return.
We save its index and continue searching to the left
because an earlier occurrence may exist.


============================================================
HOW THE SECOND BINARY SEARCH WORKS
============================================================

After finding the first occurrence, we reset:

start = 0
end   = n - 1

We perform another binary search to find the LAST
occurrence of the target.

If nums[mid] < target:
    start = mid + 1

If nums[mid] > target:
    end = mid - 1

If nums[mid] == target:
    right = mid

    We continue searching on the right side:
    start = mid + 1

IMPORTANT:
When we find the target, we save its index and continue
searching to the right because a later occurrence may exist.


============================================================
WHERE WE INITIALLY GOT STUCK
============================================================

The main conceptual challenge was understanding how to find
both the first and last occurrence of a target in a sorted
array containing duplicate values.

Initially, standard binary search may seem sufficient.
However, standard binary search can return ANY occurrence
of the target when duplicates exist.

For example:

nums = [5, 7, 7, 8, 8, 10]
target = 8

A normal binary search could return index 3 or index 4.

But the problem specifically requires both positions:

First occurrence = 3
Last occurrence  = 4

HOW WE SOLVED IT:
-----------------
Instead of returning immediately when we find the target,
we save the current index and adjust the search boundaries.

For the first occurrence:
    left = mid;
    end = mid - 1;

For the last occurrence:
    right = mid;
    start = mid + 1;

This allows us to use binary search to locate the boundaries
of the target's occurrences.

The key insight is that both searches use the same general
binary search structure, but the search direction changes
when the target is found.


============================================================
COMPLETE C++ SOLUTION
============================================================

NOTE:
The solution below is kept exactly as originally written.
No changes have been made to the code.
*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;
        int left = -1;
        int right = -1;

        if (n == 0) {
            return {left, right};
        }

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] < target) {
                start = mid + 1;
            }

            else if (nums[mid] > target) {
                end = mid - 1;
            }

            else {
                left = mid;
                end = mid - 1;
            }
        }

        start = 0;
        end = n - 1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] < target) {
                start = mid + 1;
            }

            else if (nums[mid] > target) {
                end = mid - 1;
            }

            else {
                right = mid;
                start = mid + 1;
            }
        }

        return {left, right};
    }
};


/*
============================================================
STEP-BY-STEP DRY RUN
============================================================

Input:
nums = [5, 7, 7, 8, 8, 10]
target = 8

Indices:
         0  1  2  3  4   5
nums = [ 5, 7, 7, 8, 8, 10 ]


PART 1: FIND THE FIRST OCCURRENCE
---------------------------------

Initial values:
start = 0
end   = 5
left  = -1

Iteration 1:
-----------
mid = 0 + (5 - 0) / 2 = 2

nums[2] = 7

Since 7 < 8:
start = mid + 1 = 3

Current state:
start = 3
end   = 5
left  = -1

Iteration 2:
-----------
mid = 3 + (5 - 3) / 2 = 4

nums[4] = 8

The target is found.

Save the current index:
left = 4

Continue searching to the left:
end = mid - 1 = 3

Current state:
start = 3
end   = 3
left  = 4

Iteration 3:
-----------
mid = 3 + (3 - 3) / 2 = 3

nums[3] = 8

The target is found again.

Update:
left = 3

Continue searching to the left:
end = mid - 1 = 2

Current state:
start = 3
end   = 2
left  = 3

Now start > end, so the loop terminates.

First occurrence:
left = 3


PART 2: FIND THE LAST OCCURRENCE
--------------------------------

Reset the search boundaries:

start = 0
end   = 5
right = -1

Iteration 1:
-----------
mid = 0 + (5 - 0) / 2 = 2

nums[2] = 7

Since 7 < 8:
start = mid + 1 = 3

Current state:
start = 3
end   = 5
right = -1

Iteration 2:
-----------
mid = 3 + (5 - 3) / 2 = 4

nums[4] = 8

The target is found.

Save the current index:
right = 4

Continue searching to the right:
start = mid + 1 = 5

Current state:
start = 5
end   = 5
right = 4

Iteration 3:
-----------
mid = 5 + (5 - 5) / 2 = 5

nums[5] = 10

Since 10 > 8:
end = mid - 1 = 4

Current state:
start = 5
end   = 4
right = 4

Now start > end, so the loop terminates.

Last occurrence:
right = 4


FINAL RESULT:
-------------
return {left, right};

Output:
[3, 4]


============================================================
EDGE CASES
============================================================

1. EMPTY ARRAY
--------------
Input:
nums = []
target = 0

The condition n == 0 is true.

Output:
[-1, -1]

The explicit empty-array check prevents unnecessary searching.


2. TARGET DOES NOT EXIST
------------------------
Input:
nums = [1, 3, 5, 7, 9]
target = 4

Neither binary search finds the target.

left remains -1.
right remains -1.

Output:
[-1, -1]


3. TARGET APPEARS ONLY ONCE
---------------------------
Input:
nums = [1, 2, 3, 4, 5]
target = 3

Both binary searches find index 2.

Output:
[2, 2]


4. ALL ELEMENTS ARE THE TARGET
------------------------------
Input:
nums = [2, 2, 2, 2, 2]
target = 2

The first binary search continues left until it finds
the earliest index.

The second binary search continues right until it finds
the latest index.

Output:
[0, 4]


5. TARGET IS AT THE BEGINNING
-----------------------------
Input:
nums = [2, 3, 4, 5, 6]
target = 2

Output:
[0, 0]


6. TARGET IS AT THE END
-----------------------
Input:
nums = [1, 2, 3, 4, 5]
target = 5

Output:
[4, 4]


7. TARGET IS SMALLER THAN ALL ELEMENTS
--------------------------------------
Input:
nums = [3, 5, 7, 9]
target = 1

The target is not found.

Output:
[-1, -1]


8. TARGET IS LARGER THAN ALL ELEMENTS
-------------------------------------
Input:
nums = [3, 5, 7, 9]
target = 12

The target is not found.

Output:
[-1, -1]


============================================================
TIME COMPLEXITY ANALYSIS
============================================================

The first binary search takes O(log n) time.

The second binary search also takes O(log n) time.

Total time complexity:

O(log n) + O(log n)
= O(2 log n)
= O(log n)

Therefore:

TIME COMPLEXITY = O(log n)

Here, n represents the number of elements in the array.

Why is it logarithmic?

Binary search eliminates approximately half of the remaining
search space during each iteration.


============================================================
SPACE COMPLEXITY ANALYSIS
============================================================

The algorithm uses a fixed number of variables:

n, start, end, mid, left, and right.

No additional array, map, set, or recursive call stack
is required.

Therefore:

AUXILIARY SPACE COMPLEXITY = O(1)

The returned vector contains two integers, which is a
constant-sized output and does not change the auxiliary
space complexity.


============================================================
COMMON MISTAKES TO AVOID
============================================================

1. RETURNING IMMEDIATELY WHEN THE TARGET IS FOUND
-------------------------------------------------
If we return immediately after finding the target, we may
not get the first or last occurrence.

Instead, save the index and continue searching in the
required direction.


2. FORGETTING TO UPDATE THE SEARCH BOUNDARY
-------------------------------------------
For the first occurrence:
    end = mid - 1;

For the last occurrence:
    start = mid + 1;


3. FORGETTING TO RESET THE BOUNDARIES
-------------------------------------
After the first binary search, reset:

start = 0;
end = n - 1;

Otherwise, the second search might begin with boundaries
left over from the first search.


4. INITIALIZING LEFT AND RIGHT TO ZERO
--------------------------------------
If the target does not exist, zero would incorrectly suggest
that the target occurs at index 0.

Initialize both values to -1 so the absence of the target
is represented correctly.


5. USING THE WRONG LOOP CONDITION
---------------------------------
The condition:

while (start <= end)

allows the algorithm to examine the final remaining element.

Using start < end without changing the algorithm could
cause some elements not to be checked.


6. IGNORING THE EMPTY ARRAY
---------------------------
For an empty vector, n - 1 is -1.

The explicit empty-array check immediately returns [-1, -1].


============================================================
KEY LEARNINGS
============================================================

1. Binary search works efficiently on sorted arrays.

2. Standard binary search may find any occurrence of a
   duplicate target.

3. To find the FIRST occurrence, save the index and keep
   searching to the left.

4. To find the LAST occurrence, save the index and keep
   searching to the right.

5. Two logarithmic operations still produce O(log n)
   overall time complexity.

6. Resetting start and end is necessary before beginning
   the second independent binary search.

7. Initializing results to -1 handles missing targets.

8. The midpoint formula:

   mid = start + (end - start) / 2

   is commonly preferred over:

   mid = (start + end) / 2

   because it avoids potential overflow from adding start
   and end directly when both are large positive integers.


============================================================
FINAL SUMMARY
============================================================

Problem:
Find the first and last positions of a target in a sorted
array.

Approach:
Use two independent binary searches.

First occurrence:
Save left = mid and continue searching left.

Last occurrence:
Save right = mid and continue searching right.

If the target is absent:
Return [-1, -1].

Time Complexity:
O(log n)

Auxiliary Space Complexity:
O(1)

Main concept learned:
Binary search can be adapted to find boundaries rather
than simply locating an arbitrary occurrence.

============================================================
END OF FILE
============================================================
*/
