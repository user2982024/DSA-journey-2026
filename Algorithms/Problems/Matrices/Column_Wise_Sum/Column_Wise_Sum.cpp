#include <bits/stdc++.h>
using namespace std;

vector<int> columnWiseSum(int arr[][4], int row, int col) {
    vector<int> ans;
    int colSum = 0;

    for (int i = 0; i < col; i ++) {

        colSum = 0;

        for (int j = 0; j < row; j ++) {
            colSum += arr[j][i];
        }

        ans.push_back(colSum);
    }

    return ans;
}

int main() {

    int arr[3][4] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}};

    vector<int> ans = columnWiseSum(arr, 3, 4);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}