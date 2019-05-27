#include <vector>
#include <iostream>
#include <climits>

int chartFix(std::vector<int>& chart) {
  std::vector<int> toRemove;
  for (int i = 0; i < chart.size(); i++) {
    int cur = i;
    std::cout << "i=" << i << " cur=" << cur << " :" << std::endl;
    for (int j = 0; j < i; j++) {
      if (chart[j] < chart[i]) {
        cur = std::min(cur, toRemove[j] + i - j - 1);
        std::cout << "    toRemove[j]+i-j-1=" << toRemove[j] + i - j - 1 << std::endl;
      }
      std::cout << "    j=" << j << " chart[j]=" << chart[j] << " chart[i]=" << chart[i] << " cur=" << cur << std::endl;
    }
    std::cout << "  cur=" << cur << std::endl;
    toRemove.push_back(cur);
  }
  int res = INT_MAX;
  for (int i = 0; i < toRemove.size(); i++) {
    res = std::min(res, toRemove[i]);
    std::cout << "i=" << i << " val=" << toRemove[i] << std::endl;
  }
  return res;
}

int main(void)
{
    //std::vector<int> chart = {3, 2, 6, 4, 5, 1, 7};
    //std::vector<int> chart = {1, 2, 3};
    //std::vector<int> chart = {1, 1, 1, 1};
    //std::vector<int> chart = {3, 2, 1};
    //std::vector<int> chart = {9, 1, 2, 3, 4, 6, 9, 7, 10};
    //std::vector<int> chart = {4, 2, 6, 1, 9, 0, 11, 7, 12};
    std::vector<int> chart = {1, 1, 2, 3, 1, 4, 5, 6, 1};


    std::cout << chartFix(chart);
}
