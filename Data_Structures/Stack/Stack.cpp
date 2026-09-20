#include <bits/stdc++.h>
using namespace std;

int main() {

    stack<int> s;

    s.push(2);
    s.push(5);
    s.push(3);
    s.push(8);

    s.pop();
    s.pop();

    s.push(7);

    cout << s.top() << "\n";

    return 0;
}