#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

bool bigCompare(char* a, char* b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    if (lenA > lenB) return false;
    else if (lenA < lenB) return true;
    else
    {
        int i = 0;
        while (i < lenA-1 && a[i] == b[i]) i++;
        if (i < lenA && a[i] > b[i]) return false;
        else return true;
    }
}

int main() {
    int n;
    cin >> n;
    vector<char*> V(n);
    V[0] = (char*)malloc(1000000+n+1);
    cin >> V[0];
    I[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        V[i] = V[i-1] + strlen(V[i-1]) + 1;
        cin >> V[i];
        
        for (int j = i-1; j >= -1; --j)
        {
            if (j == -1 || bigCompare(V[j], V[i]))
            {
                for(int k = i; k > j+1; --k)
                {
                    I[k] = I[k-1];
                }
                I[j+1] = i;
                break;
            }
        }
*/ 
    }
    
    for (int i = 0; i < n; ++i) cout << V[I[i]] << endl;
    return 0;
}

