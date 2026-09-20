#include <bits/stdc++.h>
using namespace std;

char toLowerCase(char &ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return ch;
    }

    char temp = ch - 'A' + 'a';
    return temp;
}

int main()
{

    char c = 'A';
    cout << c << "\n";

    toLowerCase(c);

    cout << c << "\n";

    return 0;
}