#include <bits/stdc++.h>
using namespace std;

bool binarySearch(vector<int> &arr, int n, int x) {
    int start = 0;
    int end = n - 1;
    int mid = 0;

    while (start <= end) {
        mid = start + (end - start) / 2;

        if (arr[mid] == x)  {
            return true;
        }

        if (arr[mid] < x) {
            start = mid + 1;
        }

        else {
            end = mid - 1;
        }
    }

    return false;
}

int main() {
    vector<int> arr = {1, 2, 4, 5, 6, 7, 10};

    bool ans = binarySearch(arr, 7, 7);
    cout << ans;

    return 0;
}