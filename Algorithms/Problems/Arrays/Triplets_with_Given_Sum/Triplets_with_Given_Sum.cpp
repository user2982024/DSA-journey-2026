#include <bits/stdc++.h>
using namespace std;

vector<int> triplets(vector<int> &arr, int n, int x) {
    vector<int> ans;

    for (int i = 0; i < n - 2; i ++) {
        for (int j = i + 1; j < n - 1; j ++) {
            for (int k = j + 1; k < n; k ++) {
                if (arr[k] + arr[j] + arr[i] == x) {
                    ans.push_back(arr[i]);
                    ans.push_back(arr[j]);
                    ans.push_back(arr[k]);
                }
            }
        }
    }

    return ans;
}

int main() {

    vector<int> arr = {1, 2, 3, 4, 5};

    vector<int> ans = triplets(arr, 5, 12);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << "\n";
    }

    return 0;
}