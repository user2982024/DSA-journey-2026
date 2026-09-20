#include <bits/stdc++.h>
using namespace std;

bool isValidCharacter(char &ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
        return true;
    }

    return false;
}

int main() {

    char c = 'a';
    bool ans = isValidCharacter(c);

    cout << ans << "\n";

    return 0;
}