#include <bits/stdc++.h>
using namespace std;

vector<int> findCommonInThreeSortedArrays(vector<int> &arr1, int l, vector<int> &arr2, int m, vector<int> &arr3, int n) {
    vector<int> ans;
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < l && j < m && k < n) {
        if (arr1[i] == arr2[j] && arr1[i] == arr3[k]) {
            ans.push_back(arr1[i]);
            i ++;
            j ++;
            k ++;
        }

        if (arr1[i] > arr2[j] && arr1[i] > arr3[k]) {
            j ++;
            k ++;
        }

        if (arr2[j] > arr1[i] && arr2[j] > arr3[k]) {
            i ++;
            k ++;
        }

        if (arr3[k] > arr1[i] && arr3[k] > arr2[j]) {
            i ++;
            j ++;
        }

        if (arr1[i] > arr2[j] && arr1[i] == arr3[k]) {
            j ++;
        }

        if (arr1[i] > arr3[k] && arr1[i] == arr2[j]) {
            k ++;
        }

        if (arr2[j] == arr3[k] && (arr1[i] < arr2[j] || arr1[i] < arr3[k])) {
            i ++;
        }
    }

    return ans;
}

int main() {

    vector<int> arr1 = {1, 2, 3, 4, 5, 8, 9, 11};
    vector<int> arr2 = {3, 4, 5, 7, 8, 9, 11};
    vector<int> arr3 = {4, 5, 6, 7, 9, 11};

    vector<int> ans = findCommonInThreeSortedArrays(arr1, 8, arr2, 7, arr3, 6);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}