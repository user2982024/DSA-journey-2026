/*
====================================================================
Problem: Sort an Array of 0s, 1s and 2s
Sheet: Love Babbar 450 DSA Sheet
Question Number: 4
Topic: Arrays / Counting / In-place Reconstruction
Difficulty: Easy–Medium
Author: Sheikh Abrar
Journey: 100 Days of DSA
====================================================================

🧩 Problem Statement:
Given an array consisting only of values 0, 1, and 2,
sort the array in ascending order.

Example:
Input:  [0, 2, 1, 2, 0]
Output: [0, 0, 1, 2, 2]

--------------------------------------------------------------------
🧠 Approach Used: Counting + Region Reconstruction

Since the array contains only three possible values (0, 1, 2),
we do NOT need a general sorting algorithm.

Instead:
1. Count how many 0s, 1s, and 2s exist.
2. Overwrite the array in sorted order using counts.

--------------------------------------------------------------------
📌 Why Not Use HashMap?
Values are already known and limited to {0,1,2}.
Using hashmap would add unnecessary overhead.

Counting with three variables is simpler and faster.

--------------------------------------------------------------------
📌 Why Not Use std::sort()?
std::sort() takes O(n log n),
but this problem can be solved in O(n).

--------------------------------------------------------------------
📌 How Reconstruction Works

If:
zeros = 2
ones  = 1
twos  = 2

Final array should be:
[0, 0, 1, 2, 2]

We fill array in three regions:

Index range:
[0 → zeros-1]                     → fill 0
[zeros → zeros+ones-1]            → fill 1
[zeros+ones → n-1]                → fill 2

Each index written exactly once.

--------------------------------------------------------------------
🔍 Dry Run

arr = [0, 2, 1, 2, 0]

Counting:
zeros = 2
ones  = 1
twos  = 2

Reconstruction:
[0, 0, 1, 2, 2]

--------------------------------------------------------------------
⏱ Time Complexity:
Counting pass        → O(n)
Reconstruction pass  → O(n)

Total → O(n)

--------------------------------------------------------------------
🧠 Space Complexity:
O(1)
Only three counters used.
Sorting done in-place.

--------------------------------------------------------------------
⭐ Interview Note (Important)

This is a correct and efficient solution.

However, the optimal single-pass solution is:
"Dutch National Flag Algorithm"

Which partitions array in one traversal using
three pointers (low, mid, high).

This counting approach is simpler and acceptable,
but Dutch National Flag is more optimal in practice.

--------------------------------------------------------------------
⭐ Key Learning:

When values are from a small fixed range,
counting + reconstruction is powerful and simple.

Avoid unnecessary data structures.

====================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sort012(vector<int>& arr) {

        int zerosCount = 0;
        int onesCount  = 0;
        int twosCount  = 0;

        int n = arr.size();

        // Step 1: Count occurrences
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0)
                zerosCount++;
            else if (arr[i] == 1)
                onesCount++;
            else
                twosCount++;
        }

        // Step 2: Reconstruct array in sorted order

        // Fill 0s
        for (int i = 0; i < zerosCount; i++)
            arr[i] = 0;

        // Fill 1s
        for (int i = zerosCount; i < zerosCount + onesCount; i++)
            arr[i] = 1;

        // Fill 2s
        for (int i = zerosCount + onesCount; i < n; i++)
            arr[i] = 2;
    }
};

int main() {

    Solution obj;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements (only 0,1,2): ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    obj.sort012(arr);

    cout << "Sorted array: ";
    for (int x : arr)
        cout << x << " ";

    cout << endl;

    return 0;
}

// Using dutch national flag
class Solution {
  public:
    void sort012(vector<int>& arr) {
        // code here
        
        int n = arr.size();
        int low = 0; 
        int mid = 0;
        int high = n - 1;
        
        while (mid <= high) {
            if (arr[mid] == 0) {
                swap(arr[mid], arr[low]);
                low ++;
                mid ++;
            }
            
            else if (arr[mid] == 1) {
                mid ++;
            }
            
            else {
                swap(arr[mid], arr[high]);
                high --;
            }
        }
        
        
        
        
        // Counting approach
        
        // int zerosCount = 0;
        // int onesCount = 0;
        // int twosCount = 0;
        // int n = arr.size();
        
        // for (int i = 0; i < n; i ++) {
        //     if (arr[i] == 0) {
        //         zerosCount ++;
        //     }
            
        //     if (arr[i] == 1) {
        //         onesCount ++;
        //     }
            
        //     if (arr[i] == 2) {
        //         twosCount ++;
        //     }
        // }
        
        // for (int i = 0; i < zerosCount; i ++) {
        //     arr[i] = 0;
        // }
        
        // for (int i = zerosCount; i < zerosCount + onesCount; i ++) {
        //     arr[i] = 1;
        // }
        
        // for (int i = zerosCount + onesCount; i < n; i ++) {
        //     arr[i] = 2;
        // }
    }
};