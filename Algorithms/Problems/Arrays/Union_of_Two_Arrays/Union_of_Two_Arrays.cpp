#include <bits/stdc++.h>
using namespace std;

vector<int> findUnion(vector<int> &arr1, int m, vector<int> &arr2, int n) {
    set<int> ans;

    for (int i = 0; i < m; i ++) {
        ans.insert(arr1[i]);
    }

    for (int j = 0; j < n; j ++) {
        ans.insert(arr2[j]);
    }

    return vector<int>(ans.begin(), ans.end());
}

int main() {

    vector<int> arr1 = {1, 2, 3, 4, 5, 6};
    vector<int> arr2 = {4, 6, 8, 10};
    vector<int> ans = findUnion(arr1, 6, arr2, 4);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}