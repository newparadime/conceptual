#include <vector>
#include <iostream>


int main(void)
{
  int n = 25;
  int left = 1, right = n + 1;
  while (left < right-1) {
    int middle = (left + right) / 2;
    if (middle * middle <= n) {
      left = middle;
    }
    else {
      right = middle;
    }
    std::cout << "l=" << left << " m=" << middle << " r=" << right << std::endl;
  }

  return left;
}
