#include <bits/stdc++.h>
using namespace std;

void sayDigits(int n) {
    unordered_map<int, string> mapping;

    mapping[0] = "zero";
    mapping[1] = "one";
    mapping[2] = "two";
    mapping[3] = "three";
    mapping[4] = "four";
    mapping[5] = "five";
    mapping[6] = "six";
    mapping[7] = "seven";
    mapping[8] = "eight";
    mapping[9] = "nine";

    if (n == 0) {
        return;
    }

    int digit = n % 10;
    n = n / 10;
    
    sayDigits(n);
    cout << mapping[digit] << " ";

}

int main() {

    int n = 673;

    sayDigits(n);

    return 0;
}