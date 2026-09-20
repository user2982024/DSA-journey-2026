#include <bits/stdc++.h>
using namespace std;

vector<int> rowWiseSum(int arr[][5], int row, int col) {
    vector<int> ans;
    int rowSum = 0;

    for (int i = 0; i < row; i ++) {
        rowSum = 0;

        for (int j = 0; j < col; j ++) {
            rowSum += arr[i][j];
        }

        ans.push_back(rowSum);
    }

    return ans;
}

int main() {

    int arr[3][5] = {{1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}};

    vector<int> ans = rowWiseSum(arr, 3, 5);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}