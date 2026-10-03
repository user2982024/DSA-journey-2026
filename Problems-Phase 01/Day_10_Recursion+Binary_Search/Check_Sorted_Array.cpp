
/*
==========================================================
Problem: Check if an Array Is Sorted
Platform: GeeksforGeeks
Topics: Recursion, Arrays
Language: C++
==========================================================

PROBLEM STATEMENT:
Given an array of integers, determine whether the array
is sorted in non-decreasing order using recursion.

An array is sorted in non-decreasing order when every
element is less than or equal to the element after it.

Example 1:
Input:
arr = {1, 2, 3, 4, 5}

Output:
true

Explanation:
Every element is less than or equal to the next element.


Example 2:
Input:
arr = {1, 2, 4, 3, 5}

Output:
false

Explanation:
The element 4 is greater than the next element 3.


Example 3:
Input:
arr = {1, 1, 2, 2, 3}

Output:
true

Explanation:
Equal adjacent elements are allowed.


==========================================================
APPROACH: RECURSION
==========================================================

We use a helper function check(arr, i), where i is the
index of the current element being checked.

1. BASE CASE:
   If the array has zero or one element, it is sorted.

2. COMPARE ADJACENT ELEMENTS:
   Compare arr[i] with arr[i + 1].

   If arr[i] > arr[i + 1], return false because the
   array is not sorted in non-decreasing order.

3. RECURSIVE CALL:
   If the current pair is correctly ordered, call
   check(arr, i + 1) to check the next pair.

4. If all adjacent pairs are correctly ordered,
   the function eventually returns true.

==========================================================
CODE:
==========================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool check(vector<int>& arr, int i) {
        // Base case: no more adjacent pairs to check
        if (i == static_cast<int>(arr.size()) - 1) {
            return true;
        }

        // If the current pair is out of order, the array
        // is not sorted in non-decreasing order
        if (arr[i] > arr[i + 1]) {
            return false;
        }

        // Recursively check the next adjacent pair
        return check(arr, i + 1);
    }

    bool isSorted(vector<int>& arr) {
        // An empty array or a single-element array is sorted
        if (arr.size() <= 1) {
            return true;
        }

        int i = 0;

        return check(arr, i);
    }
};

/*
==========================================================
DRY RUN 1: SORTED ARRAY
==========================================================

Input:
arr = {1, 2, 3, 4}

Initial call:
check(arr, 0)


CALL 1:
----------------------------------------------------------
i = 0

Compare:
arr[0] > arr[1]
1 > 2  -> false

The pair is correctly ordered.

Next call:
check(arr, 1)


CALL 2:
----------------------------------------------------------
i = 1

Compare:
arr[1] > arr[2]
2 > 3  -> false

The pair is correctly ordered.

Next call:
check(arr, 2)


CALL 3:
----------------------------------------------------------
i = 2

Compare:
arr[2] > arr[3]
3 > 4  -> false

The pair is correctly ordered.

Next call:
check(arr, 3)


CALL 4:
----------------------------------------------------------
i = 3

i == arr.size() - 1

The base case is reached.

Return true.

Final result:
true


==========================================================
DRY RUN 2: UNSORTED ARRAY
==========================================================

Input:
arr = {1, 3, 2, 4}

Initial call:
check(arr, 0)


CALL 1:
----------------------------------------------------------
i = 0

Compare:
arr[0] > arr[1]
1 > 3  -> false

Continue:
check(arr, 1)


CALL 2:
----------------------------------------------------------
i = 1

Compare:
arr[1] > arr[2]
3 > 2  -> true

The array is not sorted.

Return false immediately.

The remaining elements do not need to be checked.

Final result:
false


==========================================================
EDGE CASES:
==========================================================

1. EMPTY ARRAY:
   arr = {}

   Output: true

   An empty array is considered sorted because there
   are no adjacent pairs violating the sorted condition.


2. SINGLE ELEMENT:
   arr = {7}

   Output: true

   No adjacent pair exists to violate the condition.


3. ALREADY SORTED:
   arr = {1, 2, 3, 4}

   Output: true


4. DESCENDING ARRAY:
   arr = {5, 4, 3, 2, 1}

   Output: false

   The first pair already violates the condition.


5. DUPLICATE ELEMENTS:
   arr = {1, 1, 2, 2, 3}

   Output: true

   Equal adjacent elements are allowed.


6. NEGATIVE NUMBERS:
   arr = {-5, -3, -1, 0, 2}

   Output: true

   Negative values are handled normally.


==========================================================
WHY DO WE USE arr[i] > arr[i + 1]?
==========================================================

The problem requires non-decreasing order.

For every adjacent pair, we need:

arr[i] <= arr[i + 1]

If this condition is violated, then:

arr[i] > arr[i + 1]

Therefore, we return false as soon as we find such a pair.

Notice that we do not use >= because duplicate elements
are allowed in a non-decreasing array.

==========================================================
TIME AND SPACE COMPLEXITY:
==========================================================

Time Complexity:
- Best case: O(1), if the first pair is out of order.
- Worst case: O(n), if the entire array must be checked.

Auxiliary Space Complexity: O(n)
- Recursive calls occupy the call stack.
- The maximum recursion depth is proportional to n.

==========================================================
KEY LEARNINGS:
==========================================================

1. An array is sorted if every adjacent pair is ordered.
2. Recursion can check one adjacent pair per call.
3. Returning false immediately avoids unnecessary calls.
4. Equal adjacent values are valid in non-decreasing order.
5. Empty and single-element arrays are sorted.
6. Recursive calls use stack space proportional to n.

==========================================================
*/