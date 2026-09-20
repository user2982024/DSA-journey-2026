#include <bits/stdc++.h>
using namespace std;

int largestSum(int arr[][3], int row, int col) {
    int ans = 0;
    int currentSum = 0;

    for (int i = 0; i < row; i ++) {

        currentSum = 0;
        
        for (int j = 0; j < col; j ++) {
            currentSum += arr[i][j];
        }

        ans = max(ans, currentSum);

    }

    return ans;
}

int main() {

    int arr[3][3] = {{1, 2, 3}, {1, 4, 6}, {2, 2, 5}};

    int ans = largestSum(arr, 3, 3);
    cout << ans << "\n";

    return 0;
}