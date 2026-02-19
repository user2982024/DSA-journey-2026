/*
===============================================================================
PROBLEM: Remove Duplicates from Sorted Array

PLATFORM: LeetCode (Problem 26)

STATEMENT:
Given a sorted array nums, remove the duplicates in-place such that each
unique element appears only once. The relative order of elements must be
preserved.

Return the number of unique elements k such that:
- The first k elements of nums contain the unique values.
- Remaining elements beyond k do not matter.

IMPORTANT CONSTRAINT:
The array must be modified in-place using O(1) extra space.

-------------------------------------------------------------------------------
EXAMPLE

Input:
[0,0,1,1,1,2,2,3,3,4]

Output:
k = 5
nums = [0,1,2,3,4,_,_,_,_,_]

-------------------------------------------------------------------------------
MY INITIAL CONFUSION (IMPORTANT LEARNING)

1. I was confused whether to return:
   - length of unique part
   OR
   - number of unique elements

Correct answer:
These are the SAME here.

Because:
We compress unique elements at the beginning.
So count of unique elements = length of valid prefix = k.

We must return k.

NOT nums.size().

-------------------------------------------------------------------------------
SECOND OBSERVATION (POINTER STARTING POSITION)

Initially I started both i and j from index 0.

That causes:
nums[i] == nums[j] at first iteration (always true)
This iteration does nothing useful.

It doesn't break correctness, but it's unnecessary.

Better approach:
- first element is always unique
- start scanning from index 1

Cleaner and standard implementation.

-------------------------------------------------------------------------------
CORE IDEA (WRITE POINTER / COMPRESSION TECHNIQUE)

Since array is sorted:
Duplicate elements are adjacent.

So we:
1. Keep first element as unique.
2. Compare each element with last unique element.
3. If different → write it next to last unique.
4. Expand unique segment forward.

This "compresses" array in-place.

-------------------------------------------------------------------------------
ALGORITHM

Let:
j = index of last unique element

Initialize:
j = 0   (first element always unique)

Traverse from i = 1 to n-1:
If nums[i] != nums[j]:
    nums[j+1] = nums[i]
    j++

Return j + 1

-------------------------------------------------------------------------------
DRY RUN

nums = [1,1,2,2,3]

Start:
j = 0

i=1 → 1 == 1 → skip
i=2 → 2 != 1 → nums[1]=2 → j=1
i=3 → 2 == 2 → skip
i=4 → 3 != 2 → nums[2]=3 → j=2

Final array:
[1,2,3,...]

Return:
j+1 = 3

-------------------------------------------------------------------------------
TIME COMPLEXITY

Single pass through array.

O(n)

-------------------------------------------------------------------------------
SPACE COMPLEXITY

No extra data structures used.

O(1)

-------------------------------------------------------------------------------
EDGE CASES

✔ empty array
✔ single element
✔ all duplicates
✔ no duplicates
✔ negative values
✔ already unique array

-------------------------------------------------------------------------------
INTERVIEW INSIGHT

This is a classic "array compression" or "write pointer" pattern.

Same technique used in:
- Move Zeroes
- Remove Element
- Stable partition problems

-------------------------------------------------------------------------------
FINAL IMPLEMENTATION
===============================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        // j tracks index of last unique element
        int j = 0;

        // start from second element (first is always unique)
        for (int i = 1; i < n; i++) {

            if (nums[i] != nums[j]) {
                nums[j + 1] = nums[i];
                j++;
            }
        }

        // number of unique elements
        return j + 1;
    }
};


// -----------------------------------------------------------------------------
// DRIVER CODE (LOCAL TESTING)
// -----------------------------------------------------------------------------
int main() {

    vector<int> nums;

    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);

    Solution obj;

    int k = obj.removeDuplicates(nums);

    cout << "Number of unique elements: " << k << endl;
    cout << "Array after compression: ";

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }

    cout << endl;

    return 0;
}