#include <bits/stdc++.h>
using namespace std;

int main() {

    // int arr[3][4];

    //  input
    // for (int i = 0; i < 3; i ++) {
    //     for (int j = 0; j < 4; j ++) {
    //         cin >> arr[i][j];
    //     }
    // }

    //  output
    // for (int i = 0; i < 3; i ++) {
    //     for (int j = 0; j < 4; j ++) {
    //         cout << arr[i][j] <<  " ";
    //     }

    //     cout << "\n";
    // }

    int arr[3][4] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}};

    for (int row = 0; row < 3; row ++) {
        for (int col = 0; col < 4; col ++) {
            cout << arr[row][col] << " ";
        }

        cout << "\n";
    }

    return 0;
}