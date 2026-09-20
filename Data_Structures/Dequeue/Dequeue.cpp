#include <bits/stdc++.h>
using namespace std;

int main() {

    deque<int> d;
    d.push_back(5);
    d.push_back(2);
    d.push_front(3);
    d.push_front(1);

    d.pop_back();
    d.pop_front();

    cout << "The current state of dequeue is: " << "\n";

    for (int i = 0; i < d.size(); i ++) {
        cout << d[i] << "\n";
    }

    // cout << "The front element of the dequeue is: " << d.front() << "\n";
    // cout << "The back element of the dequeue is: " << d.back() << "\n";

    cout << "The front element of the dequeue is: " << d.front() << "\n";
    cout << "The back element of the dequeue is: " << d.back() << "\n";

    return 0;
}