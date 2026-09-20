#include <bits/stdc++.h>
using namespace std;

int sumArray(int *arr, int n) {
    int sum = 0;

    if (n == 1) {
        return arr[0];
    }

    sum = arr[0] + sumArray(arr + 1, n - 1);
    return sum;
}

int main() {

    int arr[5] = {3, 2, 5, 1, 6};

    int ans = sumArray(arr, 5);
    cout << ans << "\n";

    return 0;
}