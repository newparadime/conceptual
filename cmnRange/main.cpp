#include <bits/stdc++.h>

using namespace std;

int main()
{
    for(int d = 1; d < 10; d++) {
        for(int a = d-1; a <= d-1; a++) {
            cout << d << " " << a << " [";
            if(a>1) cout << std::string(a-1,' ');
            for(int i = a; i <= 40;i+=d) {
                int spaces = std::min(40-i,d-1);
                cout << "X" << std::string(spaces,' ');
            }
            cout << "]\n";
        }
    }
}
