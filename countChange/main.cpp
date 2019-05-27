#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

int vectorSum(std::vector<int>& V)
{
    int sum = 0;
    for(auto& v : V) sum += v;
    return sum;
}

int leastCombinationInner(int n, int sum, std::vector<int> V)
{
    int r = -1;
    int v = V.front();
    int vSum = v;
    V.erase(V.begin());
    
    if(V.size() == 0)
    {
        if (sum % v == 0)
        {
            return sum;
        }
        else
        {
            return -1;
        }
    }
    
    while((r < 0) && (vSum < sum))
    {
        r = leastCombinationInner(n, (sum-vSum), V);
        if(r < 0) vSum += v;
    }
    
    return r;
}

int leastCombination(int n, std::vector<int> V)
{
    
    int sum = ceil(static_cast<double>(vectorSum(V))/n) * n;
    
    int r = -1;
    
    while(r < 0)
    {
        r = leastCombinationInner(n, sum, V);
        if(r < 0) sum += n;
    }
    
    return sum;
}

long long countChange(int change, std::vector<int> coins) {
    long long ways = 0;
    int j = 1;
    for(int i = 0; i < coins.size(); ++i)
    {
        std::cout << "j=" << j++ << std::endl;
        int d = 0;
        std::vector<int> C, D;
        C = coins;
        while(!C.empty())
        {
            d += C.front();
            if(change % C.front() == 0)
            {
                ways++;
            }
            D.push_back(C.front());
            C.erase(C.begin());

            std::cout << "d=" << d << std::endl;
            std::cout << "D: ";
            for(auto& e : D) std::cout << e << ' ';
            std::cout << std::endl;
            std::cout << "C: ";
            for(auto& e : C) std::cout << e << ' ';
            std::cout << std::endl;

            for(auto&c : C)
            {
                int l = leastCombination(c, D);
                std::cout << "l=" << l << std::endl;
                ways += (change-d) / l;
                std::cout << "ways=" << ways << std::endl << std::endl;
            }
        }
        C = coins;
        C.erase(C.begin());
        C.push_back(coins.front());
        coins = C;
    }    
    return ways;
}

int main(void)
{
    int change = 10;
    std::vector<int> coins = {1,3,5,6};
    
    int n = 6;
    std::vector<int> V = {3,5};
    std::cout << "lc=" << leastCombination(n, V) << std::endl;
    
    long long result = countChange(change, coins);
    std::cout << result;
    return 0;
}
