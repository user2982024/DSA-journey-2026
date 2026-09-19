/*
===============================================================================
PROBLEM: Rotate Array by One (Clockwise / Right Rotation)

SOURCE: Love Babbar DSA Sheet (Array Section)

STATEMENT:
Given an array, rotate it by one position to the right.

Right rotation by one means:
- Last element moves to front
- All other elements shift one position to the right

-------------------------------------------------------------------------------
EXAMPLE:

Input  : [1, 2, 3, 4, 5]
Output : [5, 1, 2, 3, 4]

Explanation:
Last element (5) moves to index 0.
All other elements shift right.

-------------------------------------------------------------------------------
MY APPROACH (STUDENT APPROACH)

Idea:
1. Store the last element.
2. Shift all elements one step to the right.
3. Place stored element at index 0.

This simulates rotation in-place.

-------------------------------------------------------------------------------
THINKING PROCESS

If we start shifting from left → data will be overwritten.
So we must shift from RIGHT to LEFT.

Example:
arr[i] = arr[i - 1]

This preserves values correctly.

-------------------------------------------------------------------------------
COMMON MISTAKES (IMPORTANT LEARNING)

❌ Forgetting to store last element before shifting.
   → last element gets lost permanently.

❌ Shifting from left to right.
   → overwrites values before they move.

❌ Not handling array size 0 or 1.
   → unnecessary operations or crash.

-------------------------------------------------------------------------------
EDGE CASES

✔ Empty array
✔ Single element array
✔ All same elements
✔ Negative values
✔ Large input

-------------------------------------------------------------------------------
DRY RUN

arr = [10, 20, 30, 40]

Step 1: store last
element = 40

Step 2: shift right
i = 3 → arr[3] = arr[2] → [10,20,30,30]
i = 2 → arr[2] = arr[1] → [10,20,20,30]
i = 1 → arr[1] = arr[0] → [10,10,20,30]

Step 3: place stored element
arr[0] = 40

Final → [40,10,20,30]

-------------------------------------------------------------------------------
TIME COMPLEXITY

Single traversal for shifting → O(n)

FINAL:
O(n)

-------------------------------------------------------------------------------
SPACE COMPLEXITY

Only one extra variable used.

FINAL:
O(1)

-------------------------------------------------------------------------------
INTERVIEW INSIGHT

This is the simplest rotation.

Follow-up questions may include:
✔ rotate by k positions
✔ left rotation
✔ rotation without extra space
✔ reversal algorithm

This problem builds foundation for all rotation problems.

-------------------------------------------------------------------------------
ALGORITHM SUMMARY

Store last element
Shift array right
Place stored element at front

===============================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<int> &arr) {

        int n = arr.size();

        // Handle edge cases
        if (n == 0 || n == 1) {
            return;
        }

        // Step 1: store last element
        int lastElement = arr[n - 1];

        // Step 2: shift elements right
        for (int i = n - 1; i > 0; i--) {
            arr[i] = arr[i - 1];
        }

        // Step 3: place last element at front
        arr[0] = lastElement;
    }
};


// -----------------------------------------------------------------------------
// DRIVER CODE (LOCAL TESTING)
// -----------------------------------------------------------------------------
int main() {

    vector<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    Solution obj;
    obj.rotate(arr);

    cout << "Rotated array: ";

    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}