#include <bits/stdc++.h>
using namespace std;

// vector<int> rotateArray(vector<int> &arr, int n, int k) {
//     int temp = 0;
//     int j = 0;

//     for (int i = k; i > 0; i --) {
//         temp = arr[n - 1];
//         j = n - 2;                      // For shifting, j must be n - 2 always, as in this way it will shift all elements and last element needs to be placed, so it would be in the temp.

//         while (j >= 0) {
//             arr[j + 1] = arr[j];
//             j --;
//         }

//         arr[j + 1] = temp;
//     }

//     return arr;
// }

vector<int> rotateArray(vector<int> &arr, int n, int k) {
    vector<int> ans;

    for (int i = n - k; i < n; i ++) {
        ans.push_back(arr[i]);
    }

    for (int j = 0; j < n - k; j ++) {
        ans.push_back(arr[j]);
    }

    return ans;
}

int main() {

    vector<int> arr = {1, 2, 4, 6, 10, 16};

    // rotateArray(arr, 4, 2);

    vector<int> ans = rotateArray(arr, 6, 2);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}