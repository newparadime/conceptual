#include <iostream>
#include <iomanip>
#include <vector>
#include <set>

int tableSize(int n, int m)
{
    int result = 0;
    
    for (int value = 1; value <= n * m; value++)
    {
        std::cout << "val=" << value << " mit=" << ((value-1)/std::min(n,m))+1 << std::endl;
        for (int i = ((value-1)/std::min(n,m))+1; i <= std::max(n, m); i++)
        {
            std::cout << "   i=" << i;
            if (value % i == 0)
            {
                std::cout << " VALID!";
                result++;
                std::cout << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }
    return result;
}

int multTable(int n, int m)
{
    std::vector<std::vector<int>> M(n, std::vector<int>(m));
    std::set<int> S;
    for(int i = 1; i <= M.size(); ++i)
    {
        for(int j = 1; j <= M[0].size(); ++j)
        {
            M[i-1][j-1] = i * j;
            std::cout << std::setw(3) << M[i-1][j-1] << ' ';
            S.emplace(M[i-1][j-1]);
        }
        std::cout << std::endl;
    }
    return S.size();
}

int main(void)
{
    int n = 4;
    int m = 4;
    std::cout << "sz=" << multTable(n,m) << std::endl;
    std::cout << tableSize(n,m) << std::endl;
    return 0;
}
