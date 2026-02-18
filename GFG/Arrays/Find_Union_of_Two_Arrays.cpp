/*
===============================================================================
PROBLEM: Union of Two Arrays

SOURCE: Love Babbar DSA Sheet (Array Section)

STATEMENT:
Given two arrays a[] and b[], return a vector containing the UNION of elements
present in both arrays.

Union means:
- All unique elements from both arrays
- No duplicates
- Order is sorted automatically if using set (not mandatory unless specified)

-------------------------------------------------------------------------------
EXAMPLE:

Input:
a = [1, 2, 3, 4]
b = [3, 4, 5, 6]

Output:
[1, 2, 3, 4, 5, 6]

-------------------------------------------------------------------------------
MY APPROACH (STUDENT APPROACH)

Idea:
Use a set to automatically:
1. Remove duplicates
2. Keep elements sorted
3. Insert all elements from both arrays

Steps:
1. Traverse first array → insert into set
2. Traverse second array → insert into set
3. Convert set to vector and return

This is simple and reliable for unsorted arrays.

-------------------------------------------------------------------------------
MY PERFORMANCE (PERSONAL LEARNING NOTE)

Previous problem time → 47 minutes
This problem time     → 3 minutes

Insight:
Pattern recognition improved.
Confidence in STL usage improved.
Understanding of uniqueness handling improved.

-------------------------------------------------------------------------------
COMMON MISTAKE / CONCEPTUAL CORRECTION

Initially I thought:

Time Complexity = O(n + m)

But this is NOT fully correct.

WHY?

Because std::set is implemented using a balanced binary search tree.

Each insertion takes:
O(log k)

where k = current size of set.

Total insertions = (n + m)

So actual time complexity:

O((n + m) log(n + m))

This is a very important interview-level correction.

-------------------------------------------------------------------------------
TIME COMPLEXITY

Insert elements of both arrays:
(n + m) insertions × log(n + m)

FINAL:
O((n + m) log(n + m))

-------------------------------------------------------------------------------
SPACE COMPLEXITY

Set stores unique elements → up to (n + m)

Vector output also stores union.

FINAL:
O(n + m)

-------------------------------------------------------------------------------
EDGE CASES HANDLED

✔ One array empty
✔ Both arrays empty
✔ All elements same
✔ Negative values
✔ Large arrays
✔ Unsorted input

-------------------------------------------------------------------------------
DRY RUN

a = [2, 1, 2]
b = [1, 3, 4]

Insert from a:
set = {1, 2}

Insert from b:
set = {1, 2, 3, 4}

Convert to vector:
[1, 2, 3, 4]

-------------------------------------------------------------------------------
INTERVIEW INSIGHT (VERY IMPORTANT)

If arrays are already sorted:
Better approach = Two pointer merge
Time = O(n + m)
Space = O(1) extra (excluding output)

Set approach is preferred when:
✔ Arrays are unsorted
✔ Simplicity required
✔ No in-place constraint

-------------------------------------------------------------------------------
ALGORITHM SUMMARY

Use ordered set to collect unique elements from both arrays
Return elements as vector

===============================================================================
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:

    vector<int> findUnion(vector<int>& a, vector<int>& b) {

        set<int> uniqueElements;

        int n = a.size();
        int m = b.size();

        // Insert elements of first array
        for (int i = 0; i < n; i++) {
            uniqueElements.insert(a[i]);
        }

        // Insert elements of second array
        for (int j = 0; j < m; j++) {
            uniqueElements.insert(b[j]);
        }

        // Convert set to vector
        vector<int> result(uniqueElements.begin(), uniqueElements.end());

        return result;
    }
};


// -----------------------------------------------------------------------------
// DRIVER CODE (LOCAL TESTING)
// -----------------------------------------------------------------------------
int main() {

    vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);

    vector<int> b;
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);

    Solution obj;
    vector<int> ans = obj.findUnion(a, b);

    cout << "Union: ";

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    cout << endl;

    return 0;
}