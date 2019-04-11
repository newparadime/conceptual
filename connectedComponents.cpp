#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

struct Branch {
    Branch() : parent(nullptr), value(1) {}
    Branch* parent;
    int value;
};

Branch* GetRoot(Branch* branch)
{
    if (branch->parent == nullptr)
        return branch;
    return GetRoot(branch->parent);
}

void Union(Branch* branchA, Branch* branchB)
{
    Branch* rootA = GetRoot(branchA);
    Branch* rootB = GetRoot(branchB);
    if (rootA != rootB)
    {
        if(rootA->value < rootB->value) std::swap(rootA, rootB);
        rootA->value += rootB->value;
        rootB->parent = rootA;
    }
}

int main() {
    int N, Q, I, J;
    char q;
    std::cin >> N >> Q;
    std::vector<Branch> V(N+1, Branch());
    
    while(Q--)
    {
        std::cin >> q;
        if (q == 'Q') 
        {
            std::cin >> I;
            std::cout << GetRoot(&V[I])->value << std::endl;
        }
        else /*q == M*/
        {
            std::cin >> I >> J;
            Union(&V[I], &V[J]);
        }
    }
    return 0;
}
