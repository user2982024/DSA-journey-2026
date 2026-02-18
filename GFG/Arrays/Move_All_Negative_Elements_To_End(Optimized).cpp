/*
===============================================================================
PROBLEM: Move all negative elements to the end of the array (Stable Order)

SOURCE: Love Babbar DSA Sheet (Array Section)

REQUIREMENT:
- Move all negative numbers to the end
- Maintain the original order of elements (STABLE REARRANGEMENT)
- Modify array in-place (but extra auxiliary storage allowed)

-------------------------------------------------------------------------------
EXAMPLE:

Input  : [3, -1, 4, -2, 5]
Output : [3, 4, 5, -1, -2]

Notice:
Positive numbers remain in original order: 3 -> 4 -> 5
Negative numbers remain in original order: -1 -> -2

-------------------------------------------------------------------------------
APPROACH (STABLE PARTITION USING EXTRA VECTORS)

1. Traverse the array once.
2. Store non-negative elements in vector "positive".
3. Store negative elements in vector "negative".
4. Rewrite the original array:
      - first positives
      - then negatives

WHY THIS WORKS?
Because we insert elements in vectors in traversal order,
so their relative order is preserved (stable).

-------------------------------------------------------------------------------
WHERE I (STUDENT) GOT STUCK (IMPORTANT LEARNING)

❌ Earlier mistake in merge phase:

I used "index" as both:
   - loop starting variable
   - array write position

Example of wrong logic:

    for (int i = index; i < negative.size(); i++)

If index becomes larger than vector size,
loop never runs → elements not copied.

ROOT CAUSE:
Source index and destination index must ALWAYS be separate.

Correct rule:
    vector index → always starts from 0
    array index  → continues from last filled position

This bug is very common in array merging problems.

-------------------------------------------------------------------------------
TIME COMPLEXITY:
Traversal        → O(n)
Copy positives   → O(n)
Copy negatives   → O(n)
TOTAL            → O(n)

SPACE COMPLEXITY:
Two auxiliary vectors → O(n)

-------------------------------------------------------------------------------
EDGE CASES HANDLED:
✔ All positive
✔ All negative
✔ Contains zero
✔ Single element
✔ Empty array
✔ Mixed ordering

-------------------------------------------------------------------------------
DRY RUN:

arr = [3, -1, 4, -2]

positive = [3, 4]
negative = [-1, -2]

Rewrite:

arr[0] = 3
arr[1] = 4
arr[2] = -1
arr[3] = -2

Final = [3,4,-1,-2]

-------------------------------------------------------------------------------
INTERVIEW INSIGHT:

Two-pointer partition (swap based) is NOT allowed here,
because swapping destroys order.

Stable rearrangement requires:
- extra space OR
- complex in-place shifting (not efficient)

So this is the correct optimal stable solution.

===============================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void segregateElements(vector<int>& arr) {
        // Your code goes here
        vector<int> positive;
        vector<int> negative;
        int n = arr.size();
        
        for (int i = 0; i < n; i ++) {
            if (arr[i] >= 0) {
                positive.push_back(arr[i]);
            }
            
            else {
                negative.push_back(arr[i]);
            }
        }
        
        int index = 0;
        
        for (int i = 0; i < positive.size(); i ++) {
            arr[index] = positive[i];
            index ++;
        }
        
        for (int i = 0; i < negative.size(); i ++) {
            arr[index] = negative[i];
            index ++;
        }
    }
};


// -----------------------------------------------------------------------------
// DRIVER CODE (for local testing)
// -----------------------------------------------------------------------------
int main() {

    vector<int> arr = {3, -1, 4, -2, 5};

    Solution obj;
    obj.segregateElements(arr);

    cout << "Rearranged array: ";
    for (int x : arr)
        cout << x << " ";

    cout << endl;

    return 0;
}