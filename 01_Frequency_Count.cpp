/*
DAY 1 — ARRAYS + HASHING
Problem 1: Frequency of Elements
Platform: GeeksforGeeks
Topic: unordered_map / frequency counting

SOURCE:
https://www.geeksforgeeks.org/problems/frequency-of-elements--111353/1

====================================================================
MY APPROACH
====================================================================
I first create an unordered_map<int, int> where:
    key   = element
    value = frequency of that element

Then I traverse the array once:
    freqMap[arr[i]]++;

Finally, I traverse the frequency map and put each
{element, frequency} pair into the answer vector.

Important:
- unordered_map gives O(1) average lookup/update.
- unordered_map does NOT guarantee iteration order.
- Therefore, this solution is correct when the problem does not
  require a particular output order.

====================================================================
MY ORIGINAL ATTEMPT
====================================================================
I correctly built the frequency map, but I was initially stuck on
how to put the key/value pairs into vector<vector<int>>.

The key idea was:
    ans.push_back({x.first, x.second});

where:
    x.first  = element
    x.second = frequency

I also initially considered traversing the original array again,
but that would repeat duplicate elements in the answer. Iterating
over the map avoids that.

====================================================================
FINAL VERSION OF MY APPROACH
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> countFreq(vector<int>& arr) {
        unordered_map<int, int> freqMap;
        vector<vector<int>> ans;

        for (int i = 0; i < (int)arr.size(); i++) {
            freqMap[arr[i]]++;
        }

        for (auto x : freqMap) {
            ans.push_back({x.first, x.second});
        }

        return ans;
    }
};

/*
====================================================================
COMPLEXITY
====================================================================
Let n = number of elements and k = number of distinct elements.

Time:
    O(n) average

Space:
    O(k) auxiliary space for the frequency map.
    The answer itself can also contain O(k) pairs.

====================================================================
KEY LESSON
====================================================================
"Need to count how many times each value occurs?"
        |
        v
unordered_map<value, frequency>

This is the first major Arrays + Hashing pattern of Day 1.
*/
