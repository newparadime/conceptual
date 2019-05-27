#include <iostream>
#include <iomanip>
#include <vector>
#include <set>

bool fibonacciSimpleSum2(int n) {
  std::vector<int> fib {0, 1, 2};
  int cnt = 3;

  while (fib[cnt - 1] + fib[cnt - 2] < n) {
    fib.push_back(fib[cnt - 1] + fib[cnt - 2]);
    cnt = fib.size();
  }

  for (int i = 0; i < cnt; i++) {
    if (fib[i] + fib[cnt - 1] == n) {
      return true;
    }
  }

  return false;
}

int main(void)
{
    int n = 1;
    std::cout << fibonacciSimpleSum2(n) << std::endl;
    return 0;
}
