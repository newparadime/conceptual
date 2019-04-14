#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

// Complete the solve function below.
int solve(vector<vector<int>>& shots, vector<vector<int>>& players) {
    std::map<int,int> Xl;
    std::map<int,int> Xu;
    int S = 0;
    Xl[0] = 0;
    Xu[0] = 0;
    for (auto& shot : shots) {
        auto lit = Xl.emplace(shot[0],1);
        if (!lit.second) lit.first->second++;
        auto uit = Xu.emplace(shot[1],1);
        if (!uit.second) uit.first->second++;
    }
    for (auto it = std::next(Xl.begin()); it != Xl.end(); ++it) {
        auto last = std::prev(it);
        it->second += last->second;
    }
    for (auto it = std::next(Xu.begin()); it != Xu.end(); ++it) {
        auto last = std::prev(it);
        it->second += last->second;
    }
    for (auto& player : players) {
        auto bit = std::prev(Xu.lower_bound(player[0]));
        auto eit = std::prev(Xl.upper_bound(player[1]));
        S += eit->second - bit->second;
    }

    return S;
}

int main()
{
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> X, P;
    while(n--) {
        int a, b;
        std::cin >> a >> b;
        X.emplace_back(std::vector<int>({a,b}));
    }
    while(m--) {
        int a, b;
        std::cin >> a >> b;
        P.emplace_back(std::vector<int>({a,b}));
    }

    int result = solve(X,P);
    std::cout << result << std::endl;
    return 0;
}
