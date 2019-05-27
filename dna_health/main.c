#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> G;
vector<int> H;
    
unsigned long long DNAHealth(int start, int end, string& D)
{
    unsigned long long health = 0;
    for (int i = start; i <= end; ++i)
    {
        for (int j = 0; j <= D.length()-G[i].length(); ++j)
        {
            if (G[i] == D.substr(j, G[i].length())) health += H[i];
        }
    }
    return health;
}

int main() {
    int n, k, start, end;
    unsigned long long health, minHealth = (unsigned long long)-1, maxHealth = 0;
    
    string D;
    cin >> n;
    
    G.resize(n);
    for (auto& S : G) cin >> S;
    
    H.resize(n);
    for (auto& I : H) cin >> I;
    
    cin >> k;
    for (int i = 0; i < k; ++i)
    {
        cin >> start >> end >> D;
        health = DNAHealth(start, end, D);
        if (health < minHealth) minHealth = health;
        if (health > maxHealth) maxHealth = health;
    }
    cout << minHealth << ' ' << maxHealth;
    return 0;
}

