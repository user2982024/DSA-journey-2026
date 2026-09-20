#include <bits/stdc++.h>
using namespace std;

vector<int> findFirstAndLastOccurence(vector<int> &arr, int n, int k) {
    int count = 0;
    int first = 0;
    int last = 0;

    for (int i = 0; i < n; i ++) {
        if (arr[i] == k && count == 0) {
            first = i;
            count ++;
        }
        
        if (arr[i] == k && count > 0) {
            last = i;
        }
    }

    return {first, last};
}

int main() {

    vector<int> arr = {1, 2, 3, 3, 3, 3, 4, 6};
    vector<int> ans = findFirstAndLastOccurence(arr, 8, 3);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}