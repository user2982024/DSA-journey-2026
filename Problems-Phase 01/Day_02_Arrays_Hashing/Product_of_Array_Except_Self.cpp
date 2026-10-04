#include <iostream>
#include <vector>

using namespace std;

/*
    LeetCode #238
    Product of Array Except Self

    Problem:
    Given an integer array nums, return an array answer such that:

        answer[i] = product of all elements of nums except nums[i]

    The solution must:
        1. Run in O(n) time.
        2. Not use division.
        3. Use O(1) extra space, excluding the output array.

    Example:

        Input:
        [1, 2, 3, 4]

        Output:
        [24, 12, 8, 6]

    Explanation:

        index 0:
        2 × 3 × 4 = 24

        index 1:
        1 × 3 × 4 = 12

        index 2:
        1 × 2 × 4 = 8

        index 3:
        1 × 2 × 3 = 6
*/


class Solution {
public:

    vector<int> productExceptSelf(vector<int>& nums) {

        /*
            ans will store the product of all elements
            to the LEFT of each index.

            We are allowed to use the output array as
            extra storage because the problem does not
            count the output array toward the extra-space
            complexity.
        */
        vector<int> ans;

        // Stores the product of elements seen from the left.
        int leftProduct = 1;

        // Stores the product of elements seen from the right.
        int rightProduct = 1;

        int n = nums.size();


        /*
            The first element has nothing on its left.

            Therefore:

                left product of index 0 = 1

            We use 1 because it is the multiplicative
            identity and does not affect multiplication.
        */
        ans.push_back(1);


        /*
            FIRST PASS — LEFT TO RIGHT

            Build the left products.

            Example:

                nums = [1, 2, 3, 4]

                ans becomes:

                [1, 1, 2, 6]

            Meaning:

                index 0 → product on left = 1
                index 1 → product on left = 1
                index 2 → product on left = 1 × 2 = 2
                index 3 → product on left = 1 × 2 × 3 = 6
        */
        for (int i = 1; i < n; i++) {

            leftProduct *= nums[i - 1];

            ans.push_back(leftProduct);
        }


        /*
            SECOND PASS — RIGHT TO LEFT

            Now calculate the product from the RIGHT side.

            We don't need another array.

            rightProduct stores the product of all elements
            to the right of the current index.

            We multiply:

                left product × right product

            to obtain the final answer.
        */
        for (int j = n - 1; j >= 0; j--) {

            // Combine the left and right products.
            ans[j] *= rightProduct;

            // Include the current element for the next index.
            rightProduct *= nums[j];
        }


        return ans;
    }
};


/*
    ------------------------------------------------------------
    APPROACH
    ------------------------------------------------------------

    For every index:

        answer[i] =
            product of elements on the LEFT
            ×
            product of elements on the RIGHT


    Example:

        nums = [1, 2, 3, 4]


        index 0:

            left  = 1
            right = 2 × 3 × 4 = 24

            answer = 1 × 24 = 24


        index 1:

            left  = 1
            right = 3 × 4 = 12

            answer = 1 × 12 = 12


        index 2:

            left  = 1 × 2 = 2
            right = 4

            answer = 2 × 4 = 8


        index 3:

            left  = 1 × 2 × 3 = 6
            right = 1

            answer = 6 × 1 = 6


        Final answer:

            [24, 12, 8, 6]


    ------------------------------------------------------------
    WHY TWO PASSES?
    ------------------------------------------------------------

    First pass:

        Left → Right

        Build and store the left products in ans[].


    Second pass:

        Right → Left

        Calculate rightProduct and multiply it into
        the already stored left products.


    We therefore don't need separate:

        left[]
        right[]

    arrays.


    ------------------------------------------------------------
    IMPORTANT OBSERVATION
    ------------------------------------------------------------

    For the first element, there is nothing on its left.

        left product = 1


    For the last element, there is nothing on its right.

        right product = 1


    This works because 1 is the multiplicative identity:

        x × 1 = x


    ------------------------------------------------------------
    COMPLEXITY
    ------------------------------------------------------------

    Time Complexity:

        O(n)

    We traverse the array twice:

        First pass  → O(n)
        Second pass → O(n)

        O(n) + O(n) = O(n)


    Space Complexity:

        O(1) extra space

    We only use:

        leftProduct
        rightProduct

    The output array ans[] is not counted as extra space
    according to the problem's requirement.


    ------------------------------------------------------------
    IMPORTANT LEARNING
    ------------------------------------------------------------

    This problem demonstrates an important array pattern:

        INFORMATION BEFORE CURRENT INDEX
                    +
        INFORMATION AFTER CURRENT INDEX
                    ↓
              FINAL ANSWER


    Here:

        LEFT PRODUCT × RIGHT PRODUCT

    This pattern is especially useful when a problem asks
    for information about everything except the current
    element.
*/