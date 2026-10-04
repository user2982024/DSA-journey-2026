
/*
============================================================
Problem: Search Insert Position
Platform: LeetCode
Problem Number: 35
Topic: Binary Search
Difficulty: Easy
============================================================

PROBLEM STATEMENT:
------------------
Given a sorted array of distinct integers and a target value,
return the index if the target is found.

If the target is not found, return the index where it would
be inserted in order to maintain the sorted array.

The solution must have O(log n) runtime complexity.


EXAMPLE 1:
----------
Input:
nums = [1, 3, 5, 6]
target = 5

Output:
2

Explanation:
The target 5 exists at index 2.


EXAMPLE 2:
----------
Input:
nums = [1, 3, 5, 6]
target = 2

Output:
1

Explanation:
The target 2 does not exist, but inserting it at index 1
would maintain the sorted order:

[1, 2, 3, 5, 6]


EXAMPLE 3:
----------
Input:
nums = [1, 3, 5, 6]
target = 7

Output:
4

Explanation:
The target is greater than every element, so it would be
inserted at the end of the array.


EXAMPLE 4:
----------
Input:
nums = [1, 3, 5, 6]
target = 0

Output:
0

Explanation:
The target is smaller than every element, so it would be
inserted at the beginning of the array.


============================================================
APPROACH: BINARY SEARCH
============================================================

The array is sorted, so binary search is an efficient
approach for finding the target or its insertion position.

We initialize the following variables:

n        = nums.size()
start    = 0
end      = n - 1
position = -1

The variable position stores a possible insertion position
when we encounter an element greater than the target.

We repeatedly calculate the middle index:

mid = start + (end - start) / 2

Then we compare nums[mid] with target.


CASE 1: nums[mid] < target
--------------------------
The middle element is smaller than the target.

Therefore, the target or its insertion position must be
to the right of mid.

Update:
start = mid + 1


CASE 2: nums[mid] > target
--------------------------
The middle element is greater than the target.

The target could be inserted at mid, because inserting it
before nums[mid] would preserve the sorted order.

Save the current index:
position = mid

Continue searching to the left for a potentially smaller
valid insertion index.

Update:
end = mid - 1


CASE 3: nums[mid] == target
---------------------------
The target already exists in the array.

Return its current index immediately:
return mid;


AFTER THE LOOP:
---------------
If the target is not found, the loop terminates when:

start > end

At this point, start indicates the insertion position.

In the original solution, we use position to remember
an index where an element greater than the target was found.

If position is still -1, it means we never encountered
an element greater than the target.

This happens when the target is greater than all elements
or when the array is empty.

In that case:
position = start;

Finally, return position.


============================================================
COMPLETE C++ SOLUTION
============================================================

NOTE:
The following solution is kept exactly as originally
written. No changes have been made to your code.
*/

#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int start = 0;
        int end = n - 1;
        int position = -1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] < target) {
                start = mid + 1;
            }

            else if (nums[mid] > target) {
                position = mid;
                end = mid - 1;
            }

            else {
                return mid;
            }
        }

        if (position == -1) {
            position = start;
        }

        return position;
    }
};


/*
============================================================
STEP-BY-STEP DRY RUNS
============================================================


DRY RUN 1: TARGET EXISTS
------------------------

Input:
nums = [1, 3, 5, 6]
target = 5

Indices:
         0  1  2  3
nums = [ 1, 3, 5, 6 ]

Initial values:
start = 0
end = 3
position = -1


Iteration 1:
------------
mid = 0 + (3 - 0) / 2
mid = 1

nums[1] = 3

Since 3 < 5:
start = mid + 1
start = 2

Current state:
start = 2
end = 3
position = -1


Iteration 2:
------------
mid = 2 + (3 - 2) / 2
mid = 2

nums[2] = 5

Since nums[mid] == target:
return mid;

Output:
2

The target was found, so the function returns immediately.


------------------------------------------------------------
DRY RUN 2: TARGET NEEDS TO BE INSERTED IN THE MIDDLE
------------------------------------------------------------

Input:
nums = [1, 3, 5, 6]
target = 2

Initial values:
start = 0
end = 3
position = -1


Iteration 1:
------------
mid = 0 + (3 - 0) / 2
mid = 1

nums[1] = 3

Since 3 > 2:
position = mid
position = 1

Move left:
end = mid - 1
end = 0

Current state:
start = 0
end = 0
position = 1


Iteration 2:
------------
mid = 0 + (0 - 0) / 2
mid = 0

nums[0] = 1

Since 1 < 2:
start = mid + 1
start = 1

Current state:
start = 1
end = 0
position = 1

Now start > end, so the loop terminates.

The target does not exist.

Since position is not -1, it remains 1.

Output:
1

Explanation:
Inserting 2 at index 1 produces:

[1, 2, 3, 5, 6]


------------------------------------------------------------
DRY RUN 3: TARGET IS GREATER THAN ALL ELEMENTS
------------------------------------------------------------

Input:
nums = [1, 3, 5, 6]
target = 7

Initial values:
start = 0
end = 3
position = -1


Iteration 1:
------------
mid = 0 + (3 - 0) / 2
mid = 1

nums[1] = 3

Since 3 < 7:
start = mid + 1
start = 2


Iteration 2:
------------
mid = 2 + (3 - 2) / 2
mid = 2

nums[2] = 5

Since 5 < 7:
start = mid + 1
start = 3


Iteration 3:
------------
mid = 3 + (3 - 3) / 2
mid = 3

nums[3] = 6

Since 6 < 7:
start = mid + 1
start = 4

Now:
start = 4
end = 3

The loop terminates.

position is still -1 because no element greater than
the target was found.

Therefore:
position = start
position = 4

Output:
4

Explanation:
The target would be inserted at the end of the array.


------------------------------------------------------------
DRY RUN 4: TARGET IS SMALLER THAN ALL ELEMENTS
------------------------------------------------------------

Input:
nums = [1, 3, 5, 6]
target = 0

Initial values:
start = 0
end = 3
position = -1


Iteration 1:
------------
mid = 0 + (3 - 0) / 2
mid = 1

nums[1] = 3

Since 3 > 0:
position = 1
end = 0


Iteration 2:
------------
mid = 0 + (0 - 0) / 2
mid = 0

nums[0] = 1

Since 1 > 0:
position = 0
end = -1

Now start > end, so the loop terminates.

position = 0

Output:
0

Explanation:
The target belongs at the beginning of the array.


============================================================
WHY DO WE NEED THE POSITION VARIABLE?
============================================================

Your solution uses:

int position = -1;

Whenever nums[mid] > target, it saves the current index:

position = mid;

This is useful because the current element is greater
than the target, meaning the target could be inserted
before that element.

However, there may be an even smaller valid index to
the left, so the algorithm continues searching left.

For example:

nums = [1, 3, 5, 6]
target = 4

When mid points to 5 at index 2:
position = 2

The search continues left.

Then mid points to 3 at index 1:
start moves to 2.

The loop terminates with:
position = 2

The correct insertion index is 2.

If the target is greater than every element, position
remains -1. In that situation, start reaches n, and
the algorithm uses start as the insertion position.

This is how your code handles both middle insertion
and insertion at the end.


============================================================
EDGE CASES
============================================================

1. EMPTY ARRAY
--------------
Input:
nums = []
target = 5

The loop does not execute because end = -1 and start = 0.

position remains -1.

Since position == -1:
position = start
position = 0

Output:
0


2. SINGLE ELEMENT: TARGET EXISTS
--------------------------------
Input:
nums = [5]
target = 5

Output:
0


3. SINGLE ELEMENT: TARGET IS SMALLER
------------------------------------
Input:
nums = [5]
target = 2

Output:
0


4. SINGLE ELEMENT: TARGET IS GREATER
------------------------------------
Input:
nums = [5]
target = 8

Output:
1


5. TARGET IS AT THE BEGINNING
-----------------------------
Input:
nums = [1, 3, 5, 6]
target = 1

Output:
0


6. TARGET IS AT THE END
-----------------------
Input:
nums = [1, 3, 5, 6]
target = 6

Output:
3


7. TARGET BELONGS BETWEEN TWO ELEMENTS
--------------------------------------
Input:
nums = [1, 3, 5, 6]
target = 4

Output:
2


8. TARGET IS GREATER THAN EVERY ELEMENT
---------------------------------------
Input:
nums = [1, 3, 5, 6]
target = 10

Output:
4


9. TARGET IS SMALLER THAN EVERY ELEMENT
---------------------------------------
Input:
nums = [1, 3, 5, 6]
target = 0

Output:
0


============================================================
TIME COMPLEXITY ANALYSIS
============================================================

Binary search eliminates approximately half of the remaining
search space in each iteration.

For an array containing n elements, binary search requires
O(log n) iterations in the worst case.

Therefore:

TIME COMPLEXITY = O(log n)


============================================================
SPACE COMPLEXITY ANALYSIS
============================================================

The solution uses only a fixed number of variables:

n, start, end, mid, and position.

It does not create another array or use recursion.

Therefore:

AUXILIARY SPACE COMPLEXITY = O(1)


============================================================
COMMON MISTAKES TO AVOID
============================================================

1. USING LINEAR SEARCH
----------------------
A linear search may take O(n) time.

The problem requires O(log n), so binary search is
the appropriate approach.


2. FORGETTING TO SAVE A POSSIBLE INSERTION POSITION
---------------------------------------------------
When nums[mid] > target, the current index is a possible
insertion position.

Your code saves it using:
position = mid;


3. MOVING IN THE WRONG DIRECTION
--------------------------------
If nums[mid] < target:
    start = mid + 1;

If nums[mid] > target:
    end = mid - 1;

These updates preserve the binary search logic.


4. NOT HANDLING INSERTION AT THE END
------------------------------------
If the target is larger than every element, position
remains -1.

The final condition assigns:
position = start;

Since start becomes n, the result is n.


5. CONFUSING THE INDEX WITH THE VALUE
-------------------------------------
The function returns the index where the target exists
or should be inserted, not the target value itself.


============================================================
KEY LEARNINGS
============================================================

1. A sorted array enables efficient binary search.

2. If the target exists, return its index immediately.

3. If nums[mid] < target, search to the right.

4. If nums[mid] > target, save mid as a possible insertion
   position and continue searching to the left.

5. If the target is not found, start ends at the correct
   insertion index.

6. The position variable helps preserve a candidate index,
   while start handles the case where insertion belongs
   after all existing elements.

7. The algorithm has O(log n) time complexity and O(1)
   auxiliary space complexity.


============================================================
FINAL SUMMARY
============================================================

Problem:
Search for a target in a sorted array, or find where
it should be inserted.

Approach:
Binary search.

If found:
Return mid.

If nums[mid] < target:
Move right.

If nums[mid] > target:
Save mid and move left.

If not found:
Return the saved position, or start if no candidate
was found.

Time Complexity:
O(log n)

Auxiliary Space Complexity:
O(1)

Main concept learned:
Binary search can find an insertion position without
shifting or modifying any array elements.

============================================================
END OF FILE
============================================================
*/
