#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <climits>

class bigArray {
  private:
    size_t size;
    int** list;
  public:
    static constexpr int MAX_SUBARR_SIZE = 100000000;
    bigArray (size_t s) : size(s) {
        int nSubArrays = (int)ceil(static_cast<double>(size)/MAX_SUBARR_SIZE);
        list = new int*[nSubArrays];
        for(int i = 0; i < nSubArrays; ++i)
        {
            list[i] = new int[MAX_SUBARR_SIZE];
        }
    }
    
    int& operator[] (int x) {
        if( (x < 0) || (x >= size) )
        {
            std::stringstream ss;
            ss << "bigArray: index(" << x << ") out of range. this->size:" << size << ".";
            throw std::out_of_range(ss.str());
        }
        int iSubArray = x / MAX_SUBARR_SIZE;
        int jSubArrayIndex = x % MAX_SUBARR_SIZE;
        return list[iSubArray][jSubArrayIndex];
    }
};

int nCash(std::vector<int> bills, int p)
{
    if(bills.size() == 0)
    {
        return 0;
    }
        
    if(p == 0)
    {
        auto min_it = std::min_element(bills.begin(), bills.end());
        if (*min_it == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    bigArray bT(5);
 
    int M[p+1];
    M[0] = 0;
    
    for(int i = 1; i <= p; ++i)
    {
        M[i] = INT_MAX;
    }
    
    for(int i = 1; i <= p; ++i)
    {
        if(i % 1000000 == 0)
        {
            std::cout << i << ' ';
        }
        for(int j = 0; j < bills.size(); ++j)
        {
            if (bills[j] <= i)
            {
                if ( (M[i-bills[j]] != INT_MAX) && (M[i-bills[j]] + 1 < M[i]) )
                {
                    M[i] = M[i-bills[j]] + 1;
                }
            }
        }
    }
    std::cout << std::endl;
    
    return M[p];
}

int main(void)
{
    std::cout << "std=" << __cplusplus << std::endl;
    std::cout << nCash({1,5,10,20,50,10}, 99);
    return 0;
}
