/*
===============================================================================
PROBLEM: Product of Array Except Self
Platform: LeetCode

Given an integer array nums, return an array answer such that:

answer[i] = product of all elements of nums except nums[i]

Constraints:
- You must NOT use division.
- Solve in O(n) time.
- Extra space should be O(1) (excluding output array).

Example:
Input:  [1,2,3,4]
Output: [24,12,8,6]
===============================================================================
*/

/*
===============================================================================
INTUITION

Brute force approach:
For each index i:
  multiply all elements except i
Time complexity = O(n^2) ❌ too slow

Division approach:
totalProduct / nums[i]
But division is NOT allowed ❌
Also fails when zeros exist.

Optimized idea:

For each index i:
answer[i] =
(product of elements to LEFT of i)
×
(product of elements to RIGHT of i)

Compute these efficiently using prefix and suffix products.
===============================================================================
*/

/*
===============================================================================
CORE INVARIANT

During first pass (left → right):
ans[i] stores product of all elements BEFORE index i.

During second pass (right → left):
Multiply ans[i] by product of all elements AFTER index i.

Final:
ans[i] = left_product × right_product
===============================================================================
*/

/*
===============================================================================
ALGORITHM

1. Create result array ans of size n.

2. Left pass:
   Maintain leftProduct.
   ans[i] = leftProduct
   leftProduct *= nums[i]

3. Right pass:
   Maintain rightProduct.
   ans[i] *= rightProduct
   rightProduct *= nums[i]

4. Return ans.
===============================================================================
*/

/*
===============================================================================
EDGE CASES

1. Array contains zero(s)
   Works naturally without special handling.

2. Single element
   Result = [1] (no other elements)

3. Negative numbers
   Works correctly with multiplication rules.
===============================================================================
*/

/*
===============================================================================
DRY RUN

nums = [1, 2, 3, 4]

LEFT PASS
i   leftProduct   ans[i]
------------------------
0      1            1
1      1            1
2      2            2
3      6            6

ans = [1,1,2,6]

RIGHT PASS
i   rightProduct   ans[i] *= rightProduct
-----------------------------------------
3      1             6
2      4             8
1     12            12
0     24            24

Final = [24,12,8,6]
===============================================================================
*/

/*
===============================================================================
TIME & SPACE COMPLEXITY

Time Complexity  : O(n)
Space Complexity : O(1) extra (output array not counted)

Two linear passes.
===============================================================================
*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        int n = nums.size();
        vector<int> ans(n);

        int leftProduct = 1;

        // First pass: store left products
        for (int i = 0; i < n; i++) {
            ans[i] = leftProduct;
            leftProduct *= nums[i];
        }

        int rightProduct = 1;

        // Second pass: multiply right products
        for (int i = n - 1; i >= 0; i--) {
            ans[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return ans;
    }
};