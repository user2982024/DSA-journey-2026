
/*
==========================================================
Problem: Reverse an Array Using Recursion
Platform: GeeksforGeeks
Topics: Recursion, Arrays, Two Pointers
Language: C++
==========================================================

PROBLEM STATEMENT:
Given an array of integers, reverse the array in place
using recursion.

The first element should become the last element, the
second element should become the second-last element,
and so on.

Example 1:
Input:
arr = {1, 2, 3, 4, 5}

Output:
{5, 4, 3, 2, 1}


Example 2:
Input:
arr = {10, 20, 30, 40}

Output:
{40, 30, 20, 10}


Example 3:
Input:
arr = {7}

Output:
{7}

==========================================================
APPROACH: RECURSION + TWO POINTERS
==========================================================

We use two pointers:

1. start:
   Points to the first element that has not been processed.

2. end:
   Points to the last element that has not been processed.

ALGORITHM:

1. BASE CASE:
   If start >= end, return.

   This means the pointers have met or crossed each other.
   The entire array has been reversed.

2. SWAP:
   Swap arr[start] and arr[end].

3. MOVE THE POINTERS:
   Move start one position forward.
   Move end one position backward.

4. RECURSIVE CALL:
   Call reverse(arr, start + 1, end - 1).

5. Repeat until the base case is reached.

==========================================================
CODE:
==========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void reverse(vector<int>& arr, int start, int end) {
        // Base case: pointers meet or cross
        if (start >= end) {
            return;
        }

        // Swap the elements at both ends
        swap(arr[start], arr[end]);

        // Recursively reverse the remaining inner portion
        reverse(arr, start + 1, end - 1);
    }

    void reverseArray(vector<int>& arr) {
        int n = arr.size();

        int start = 0;
        int end = n - 1;

        reverse(arr, start, end);
    }
};

/*
==========================================================
DRY RUN:
==========================================================

Input:
arr = {1, 2, 3, 4, 5}

Initial state:
start = 0
end   = 4

Array:
{1, 2, 3, 4, 5}


CALL 1:
----------------------------------------------------------
reverse(arr, 0, 4)

start < end, so swap arr[0] and arr[4].

Swap:
1 <-> 5

Array becomes:
{5, 2, 3, 4, 1}

Next recursive call:
reverse(arr, 1, 3)


CALL 2:
----------------------------------------------------------
reverse(arr, 1, 3)

start < end, so swap arr[1] and arr[3].

Swap:
2 <-> 4

Array becomes:
{5, 4, 3, 2, 1}

Next recursive call:
reverse(arr, 2, 2)


CALL 3:
----------------------------------------------------------
reverse(arr, 2, 2)

Here, start >= end.

The base case is reached, so the function returns.

Final array:
{5, 4, 3, 2, 1}

==========================================================
EDGE CASES:
==========================================================

1. EMPTY ARRAY:
   arr = {}

   start = 0
   end = -1

   Since start >= end, the function returns immediately.

   Output:
   {}


2. SINGLE ELEMENT:
   arr = {7}

   start = 0
   end = 0

   Since start >= end, no swap is needed.

   Output:
   {7}


3. TWO ELEMENTS:
   arr = {1, 2}

   Swap arr[0] and arr[1].

   Output:
   {2, 1}


4. ODD NUMBER OF ELEMENTS:
   arr = {1, 2, 3, 4, 5}

   The middle element remains in its original position.

   Output:
   {5, 4, 3, 2, 1}


5. EVEN NUMBER OF ELEMENTS:
   arr = {1, 2, 3, 4}

   The pointers cross after the necessary swaps.

   Output:
   {4, 3, 2, 1}


==========================================================
WHY DOES THE BASE CASE USE start >= end?
==========================================================

There are two situations:

1. start == end:
   Both pointers point to the same middle element.
   No swap is required.

2. start > end:
   The pointers have crossed.
   All required swaps have already been completed.

Therefore, start >= end correctly terminates recursion.

==========================================================
TIME AND SPACE COMPLEXITY:
==========================================================

Time Complexity: O(n)
- Approximately n / 2 swaps are performed.
- Each recursive call performs constant work.

Auxiliary Space Complexity: O(n)
- Recursive calls use the call stack.
- The maximum recursion depth is approximately n / 2.

==========================================================
KEY LEARNINGS:
==========================================================

1. Recursion can be combined with the two-pointer technique.
2. Swapping the outer elements reverses their positions.
3. Moving both pointers inward reduces the problem size.
4. The middle element does not need to be swapped.
5. The array is modified in place; no second array is needed.
6. Passing the array by reference allows changes to persist.
7. The recursive call stack uses O(n) auxiliary space.

==========================================================
*/