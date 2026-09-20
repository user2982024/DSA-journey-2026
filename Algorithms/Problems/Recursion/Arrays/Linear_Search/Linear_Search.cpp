#include <bits/stdc++.h>
using namespace std;

bool linearSearch(int *arr, int n, int k) {
    if (n == 0) {
        return false;
    }

    if (arr[0] == k) {
        return true;
    }

    return linearSearch(arr + 1, n - 1, k);
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int key = 5;

    bool ans = linearSearch(arr, 5, key);
    cout << ans << "\n";

    return 0;
}