#include <bits/stdc++.h>
using namespace std;

// vector<int> pairSum(vector<int> &arr, int n, int x) {
//     vector<int> ans;

//     for (int i = 0; i < n - 1; i ++) {
//         for (int j = i + 1; j < n; j ++) {
//             if (arr[j] + arr[i] == x) {
//                 ans.push_back(arr[i]);
//                 ans.push_back(arr[j]);
//             }
//         }
//     }

//     return ans;
// }

vector<int> pairSum(vector<int> &arr, int n, int x) {
    sort(arr.begin(), arr.end());
    vector<int> ans;

    int start = 0;
    int end = n - 1;

    while (start < end) {
        if (arr[start] + arr[end] == x) {
            ans.push_back(arr[start]);
            ans.push_back(arr[end]);
            start ++;
            end --;
        }

        if (arr[start] + arr[end] < x) {
            start ++;
        }
        
        if (arr[start] + arr[end] > x) {
            end --;
        }
    }

    return ans;
}

int main() {

    vector<int> arr = {4, 5, 3, 1, 2, 7, 6};
 
    vector<int> ans = pairSum(arr, 7, 7);
  
    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << "\n";
    }

    return 0;
}