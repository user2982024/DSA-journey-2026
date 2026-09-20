#include <bits/stdc++.h>
using namespace std;

// Merging 2 sorted arrays without using extra space
vector<int> mergeSortedArrays(vector<int> &arr1, int m, vector<int> &arr2, int n) {
    for (int i = 0; i < n; i ++) {
        arr1.push_back(arr2[i]);
    }

    sort(arr1.begin(), arr1.end());

    return arr1;
}

int main() {

    vector<int> arr1 = {1, 4, 6, 10, 12};
    vector<int> arr2 = {2, 3, 13, 20};

    mergeSortedArrays(arr1, 5, arr2, 4);

    for (int i = 0; i < arr1.size(); i ++) {
        cout << arr1[i] << " ";
    }

    return 0;
}