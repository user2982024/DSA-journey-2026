#include <bits/stdc++.h>
using namespace std;

bool subarraySumEqualsX(vector<int> &arr, int n, int x) {
    int j = 0;
    int currentSum = 0;

    for (int i = 0; i < n - 1; i ++) {
        j = i + 1;
        currentSum = arr[i];

        while (currentSum <= x) {
            currentSum += arr[j];

            if (currentSum == x) {
                return true;
            }

            j ++;
        }
    }

    return false;
}

int main() {

    vector<int> arr = {1, 3, 2, 5, 1, 1, 2, 3};

    bool ans = subarraySumEqualsX(arr, 8, 8);
    cout << ans << "\n";

    return 0;
}