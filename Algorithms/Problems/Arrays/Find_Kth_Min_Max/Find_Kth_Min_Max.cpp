#include <bits/stdc++.h>
using namespace std;

vector<int> findKthMinMax(vector<int> &arr, int n, int k) {
    sort(arr.begin(), arr.end());

    return {arr[k - 1], arr[n - k]};

    

    // set<int> s;

    // for (int i = 0; i < n; i ++) {
    //     s.insert(arr[i]);
    // }

    // return {*s.begin() + k - 1, *s.end() - k};
}

int main() {

    vector<int> arr = {1, 2, 10, 4, 6, 3, 8, 2};

    vector<int> ans = findKthMinMax(arr, 8, 3);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}
