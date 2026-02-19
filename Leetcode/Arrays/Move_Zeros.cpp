/*
===============================================================================
PROBLEM: Move Zeroes

PLATFORM: LeetCode

STATEMENT:
Given an integer array nums, move all zeros to the end of the array while
maintaining the relative order of the non-zero elements.

You must perform the operation in-place.

-------------------------------------------------------------------------------
EXAMPLE:

Input  : [0, 1, 0, 3, 12]
Output : [1, 3, 12, 0, 0]

Relative order of non-zero elements must remain unchanged.

-------------------------------------------------------------------------------
MY INITIAL THINKING (STUDENT APPROACH)

Since order must be preserved (stable rearrangement),
I first thought extra space is required.

So I created:
- one vector for non-zero elements
- one vector for zeros

Then I rewrote the original array:
1. copy non-zero elements
2. append zeros

This works correctly but uses extra space O(n).

-------------------------------------------------------------------------------
WHY THIS APPROACH WORKS

Because:
- we collect elements in original order
- then rewrite sequentially
- no swapping occurs
- stability preserved

-------------------------------------------------------------------------------
COMMON MISCONCEPTION (IMPORTANT LEARNING)

I initially believed:
Stable rearrangement always requires extra space.

This is NOT always true.

In this problem, we can do stable movement in-place using a
write pointer technique.

This gives:
Time  O(n)
Space O(1)

This is the optimal interview solution.

-------------------------------------------------------------------------------
OPTIMAL IN-PLACE APPROACH (FINAL RECOMMENDED)

Idea:
1. Maintain index 'insertPos' where next non-zero should go.
2. Traverse array:
      if element is non-zero → place at insertPos and increment insertPos
3. After placing all non-zeros → fill remaining positions with zero.

No swapping.
Order preserved.
Constant space.

-------------------------------------------------------------------------------
DRY RUN (OPTIMAL APPROACH)

nums = [0,1,0,3,12]

insertPos = 0

i=0 → zero → skip
i=1 → 1 → nums[0]=1 → insertPos=1
i=2 → zero → skip
i=3 → 3 → nums[1]=3 → insertPos=2
i=4 → 12 → nums[2]=12 → insertPos=3

Now fill zeros from index 3 onward

Result → [1,3,12,0,0]

-------------------------------------------------------------------------------
TIME COMPLEXITY

Extra space solution:
O(n)

Optimal in-place solution:
O(n)

-------------------------------------------------------------------------------
SPACE COMPLEXITY

Extra space solution:
O(n)

Optimal solution:
O(1)

-------------------------------------------------------------------------------
EDGE CASES

✔ all zeros
✔ no zeros
✔ single element
✔ empty array
✔ negative values
✔ large arrays

-------------------------------------------------------------------------------
INTERVIEW STRATEGY (BEST ANSWER FLOW)

1. Explain extra space stable approach
2. Optimize to in-place stable method

This shows algorithmic maturity.

===============================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    // ------------------------------------------------------------------------
    // OPTIMAL IN-PLACE STABLE SOLUTION (RECOMMENDED)
    // ------------------------------------------------------------------------
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        int n = nums.size();

        // Step 1: place non-zero elements in order
        for (int i = 0; i < n; i ++) {
            if (nums[i] != 0) {
                nums[j] = nums[i];
                j ++;
            }
        }

        // Step 2: fill remaining positions with zero
        for (int i = j; i < n; i ++) {
            nums[i] = 0;
        }
    }

    // ------------------------------------------------------------------------
    // ALTERNATIVE EXTRA SPACE SOLUTION (YOUR ORIGINAL IDEA)
    // ------------------------------------------------------------------------
    void moveZeroesExtraSpace(vector<int>& nums) {

        vector<int> nonZeros;
        vector<int> zeros;

        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0)
                zeros.push_back(nums[i]);
            else
                nonZeros.push_back(nums[i]);
        }

        int index = 0;

        for (int i = 0; i < nonZeros.size(); i++) {
            nums[index] = nonZeros[i];
            index++;
        }

        for (int i = 0; i < zeros.size(); i++) {
            nums[index] = zeros[i];
            index++;
        }
    }
};


// -----------------------------------------------------------------------------
// DRIVER CODE (LOCAL TESTING)
// -----------------------------------------------------------------------------
int main() {

    vector<int> nums;
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(0);
    nums.push_back(3);
    nums.push_back(12);

    Solution obj;

    obj.moveZeroes(nums);   // using optimal solution

    cout << "Result: ";

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }

    cout << endl;

    return 0;
}