#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Find the Minimum and Maximum element in an Array
    Source: Love Babbar DSA Sheet (Arrays - Q2)

    Approach:
    → Traverse the array once.
    → Keep track of the smallest (minValue) and largest (maxValue) elements.
    → Return both values in a vector of size 2.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

vector<int> getMinMax(vector<int> &arr) {
    int minValue = INT_MAX;
    int maxValue = INT_MIN;
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < minValue)
            minValue = arr[i];
        if (arr[i] > maxValue)
            maxValue = arr[i];
    }
    
    vector<int> ans(2);
    
    ans[0] = minValue;
    ans[1] = maxValue;
    
    return ans;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> result = getMinMax(arr);
    
    cout << "Minimum element = " << result[0] << endl;
    cout << "Maximum element = " << result[1] << endl;

    return 0;
}
