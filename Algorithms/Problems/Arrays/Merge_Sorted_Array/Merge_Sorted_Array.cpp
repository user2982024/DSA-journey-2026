#include <bits/stdc++.h>
using namespace std;

vector<int> mergeSortedArray(vector<int> &A, int m, vector<int> &B, int n) {
    vector<int> ans;
    int i = 0;
    int j = 0;

    while (i < m && j < n) {
        if (A[i] < B[j]) {
            ans.push_back(A[i]);
            i ++;
        }

        else {
            ans.push_back(B[j]);
            j ++;
        }
    }

    while (i < m) {
        ans.push_back(A[i]);
        i ++;
    }

    while (j < n) {
        ans.push_back(B[j]);
        j ++;
    }

    return ans;
}

int main() {

    vector<int> arr1 = {1, 3, 5, 7, 9};
    vector<int> arr2 = {2, 4, 6};

    vector<int> v = mergeSortedArray(arr1, 5, arr2, 3);

    for (int i = 0; i < v.size(); i ++) {
        cout << v[i] << " ";
    }

    return 0;
}