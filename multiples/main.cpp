#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

int minPopFront(std::deque<int>& D, std::deque<int>& E, std::vector<int>& a, std::vector<int>& M)
{
    int j;
    if(E.empty())
    {
        j = D.front();
        D.pop_front();
    }
    else if(D.empty())
    {
        j = E.front();
        E.pop_front();
    }
    else if (a[D.front()] * M[D.front()] < a[E.front()] * M[E.front()])
    {
        j = D.front();
        D.pop_front();
    }
    else if (a[E.front()] * M[E.front()] < a[D.front()] * M[D.front()])
    {
        j = E.front();
        E.pop_front();
    }
    else if (D.front() < E.front())
    {
        j = D.front();
        D.pop_front();
    }
    else
    {
        j = E.front();
        E.pop_front();
    }
    return j;
}

int minFront(std::deque<int>& D, std::deque<int>& E, std::vector<int>& a, std::vector<int>& M)
{
    if(E.empty())
        return D.front();
    else if(D.empty())
        return E.front();
    else if (a[D.front()] * M[D.front()] < a[E.front()] * M[E.front()])
        return D.front();
    else if (a[E.front()] * M[E.front()] < a[D.front()] * M[D.front()])
        return E.front();
    else if (D.front() < E.front())
        return D.front();
    else
        return E.front();
}

void minPushBack(std::deque<int>& D, std::deque<int>& E, std::vector<int>& a, std::vector<int>& M, int j)
{
    if (D.empty())
        D.push_back(j);
    else if (E.empty())
        E.push_back(j);
    else if (a[j] * M[j] >= a[D.back()] * M[D.back()])
        D.push_back(j);
    else
        E.push_back(j);
}

int findNthSmallestMultiple(std::vector<int> a, int n) {
    std::sort(a.begin(), a.end());
    std::vector<int> M(a.size(), 1);
    std::vector<int> V;
    std::deque<int> D;
    std::deque<int> E;
    int j, k;
    for (int i = 0; i < a.size(); ++i) D.push_back(i);
    while (V.size() < n)
    {
        j = minPopFront(D, E, a, M);
        k = minFront(D, E, a, M);
        std::cout << "j=" << j << " k=" << k << std::endl;
        while (a[j] * M[j] <= a[k] * M[k])
        {
            if (V.empty() || a[j] * M[j] > V.back())
                V.push_back(a[j] * M[j]);
            M[j]++;
        }
        minPushBack(D, E, a, M, j);
        for(auto& v : V) std::cout << v << ' ';
        std::cout << std::endl;
    }
    for(auto& v : V) std::cout << v << ' ';
    std::cout << std::endl;
    return V[n-1];
}

int main(void)
{
    std::vector<int> A = {4, 10, 2};
    std::cout << "ans=" << findNthSmallestMultiple(A, 4) << std::endl;
    return 0;
}

