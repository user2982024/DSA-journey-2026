#include <bits/stdc++.h>
using namespace std;

int findCommonElements(vector<int> &arr1, int m, vector<int> &arr2, int n) {
    unordered_set<int> s;
    int count = 0;

    for (int i = 0; i < n; i ++) {
        s.insert(arr2[i]);
    }

    for (int j = 0; j < m; j ++) {
        if (s.find(arr1[j]) != s.end()) {
            count ++;
        }
    }

    return count;
}

int main() {

    vector<int> arr1 = {2, 3, 6, 1, 9, 4};
    vector<int> arr2 = {20, 60, 10, 90};

    int ans = findCommonElements(arr1, 6, arr2, 4);
    cout << ans << "\n";

    return 0;
}