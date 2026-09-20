#include <bits/stdc++.h>
using namespace std;

vector<int> intersectionOfTwoArrays(vector<int> &arr1, int m, vector<int> &arr2, int n) {
    unordered_multiset<int> s;
    vector<int> ans;

    for (int i = 0; i < m; i ++) {
        s.insert(arr1[i]);
    }

    for (int j = 0; j < n; j ++) {
        if (s.find(arr2[j]) != s.end()) {
            ans.push_back(arr2[j]);
            s.erase(s.find(arr2[j]));
        }
    }

    return ans;
}

int main() {

    vector<int> arr1 = {0, 1, 1, 0, 1};
    vector<int> arr2 = {1, 0, 1, 1};

    vector<int> res = intersectionOfTwoArrays(arr1, 5, arr2, 4);

    for (int i = 0; i < res.size(); i ++) {
        cout << res[i] << "\n";
    }

    return 0;
}