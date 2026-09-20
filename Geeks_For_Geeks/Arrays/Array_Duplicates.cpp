/*
====================================================================
PROBLEM: Find Duplicates in an Array
Platform: GeeksforGeeks / Interview Standard
Author: Sheikh Abrar (DSA Challenge)
====================================================================

PROBLEM STATEMENT
-----------------
Given an array of integers, return all elements that appear more
than once (duplicates).

Duplicates should be detected correctly regardless of order.

Example:
Input  : [1, 2, 3, 1, 3, 6, 6]
Output : [1, 3, 6]

--------------------------------------------------------------------
APPROACH 1 — HASH MAP (FREQUENCY COUNTING)
--------------------------------------------------------------------

IDEA
----
Count how many times each element appears.
If frequency > 1 → duplicate.

STEPS
-----
1. Traverse array and store frequencies in unordered_map.
2. Traverse map and collect keys with freq > 1.

WHY IT WORKS
------------
Map stores count of occurrences.
Duplicate elements are exactly those with count > 1.

TIME COMPLEXITY
---------------
Counting frequencies  -> O(N)
Traversing map        -> O(M) where M = unique elements
Since M ≤ N → O(N)

SPACE COMPLEXITY
----------------
O(N) for hashmap (worst case all elements unique)

ADVANTAGES
----------
✔ Very clear logic
✔ Works for any value range
✔ Easy to explain in interviews

DISADVANTAGES
-------------
✔ Uses extra memory
✔ Two passes (array + map)

--------------------------------------------------------------------
APPROACH 2 — UNORDERED SET (SINGLE PASS DETECTION)
--------------------------------------------------------------------

IDEA
----
Track elements seen so far.
If element already exists in set → duplicate.

STEPS
-----
1. Traverse array once.
2. If element already in set → duplicate.
3. Otherwise insert into set.

WHY IT WORKS
------------
Set stores visited elements.
Second appearance means duplication.

TIME COMPLEXITY
---------------
Each lookup and insert is average O(1)
Total → O(N)

SPACE COMPLEXITY
----------------
O(N) in worst case (all unique elements)

ADVANTAGES
----------
✔ Single pass
✔ Simple logic
✔ Early detection of duplicates

IMPORTANT NOTE
--------------
If an element appears multiple times, it may be added multiple
times to result.

Example:
[1,1,1] → output may be [1,1]

To store duplicates only once, we must track already-added values.

--------------------------------------------------------------------
WHEN TO USE WHICH APPROACH?
--------------------------------------------------------------------

Use HASH MAP when:
✔ You want exact frequency information
✔ You need precise duplicate control
✔ You want each duplicate reported once

Use UNORDERED SET when:
✔ You only need detection
✔ Single pass preferred
✔ Frequency not required

--------------------------------------------------------------------
DRY RUN (SET APPROACH)
--------------------------------------------------------------------

Array: [4, 3, 2, 7, 8, 2, 3, 1]

Seen set evolves:

4 → insert
3 → insert
2 → insert
7 → insert
8 → insert
2 → already seen → duplicate
3 → already seen → duplicate
1 → insert

Result: [2, 3]

--------------------------------------------------------------------
EDGE CASES
--------------------------------------------------------------------
✔ No duplicates → return empty vector
✔ All elements same
✔ Negative numbers (hashing works fine)
✔ Large input size

--------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ===============================================================
    APPROACH 1 — HASH MAP (FREQUENCY COUNT)
    ===============================================================
    */
    vector<int> findDuplicates_HashMap(vector<int>& arr) {

        unordered_map<int, int> freqMap;
        vector<int> ans;

        int n = arr.size();

        // Count frequencies
        for (int i = 0; i < n; i++) {
            freqMap[arr[i]]++;
        }

        // Collect elements with freq > 1
        unordered_map<int, int>::iterator it;
        for (it = freqMap.begin(); it != freqMap.end(); it++) {
            if (it->second > 1) {
                ans.push_back(it->first);
            }
        }

        return ans;
    }


    /*
    ===============================================================
    APPROACH 2 — UNORDERED SET (SINGLE PASS)
    ===============================================================
    */
    vector<int> findDuplicates_UnorderedSet(vector<int>& arr) {

        unordered_set<int> seen;
        vector<int> ans;

        int n = arr.size();

        for (int i = 0; i < n; i++) {

            // if already seen → duplicate
            if (seen.find(arr[i]) != seen.end()) {
                ans.push_back(arr[i]);
            }

            // mark as seen
            seen.insert(arr[i]);
        }

        return ans;
    }
};