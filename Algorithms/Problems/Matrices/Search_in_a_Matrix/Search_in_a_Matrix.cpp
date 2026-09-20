#include <bits/stdc++.h>
using namespace std;

bool isPresent(int arr[][4], int row, int col, int k) {
    for (int i = 0; i < row; i ++) {
        for (int j = 0; j < col; j ++) {
            if (arr[i][j] == k) {
                return true;
            }
        }
    }

    return false;
}

int main() {

    int arr[3][4] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}};

    bool ans = isPresent(arr, 3, 4, 3);
    cout << ans << "\n";

    return 0;
}