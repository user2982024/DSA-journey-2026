// File: segregate_elements.cpp
// Author: Sheikh Abrar
// Description: Move all negative elements to the end of an array 
//              while preserving the relative order of positive and negative numbers.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void segregateElements(vector<int>& arr) {
        vector<int> positive;
        vector<int> negative;
        vector<int> ans;
        
        // Separate positive and negative elements
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] >= 0) {
                positive.push_back(arr[i]);
            } else {
                negative.push_back(arr[i]);
            }
        }
        
        // Merge positives first
        for (int i = 0; i < positive.size(); i++) {
            ans.push_back(positive[i]);
        }
        
        // Then negatives
        for (int i = 0; i < negative.size(); i++) {
            ans.push_back(negative[i]);
        }
        
        // Copy back to original array
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = ans[i];
        }
    }
};

// Helper function to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Example usage
int main() {
    Solution sol;
    vector<int> arr = {1, -1, 3, 2, -7, -5, 11, 6};
    
    cout << "Original Array: ";
    printArray(arr);
    
    sol.segregateElements(arr);
    
    cout << "After Segregation: ";
    printArray(arr);
    
    return 0;
}
