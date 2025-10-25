/*
 * Problem URL : https://codeforces.com/contest/651/problem/B
 * Submit Date : 2025-09-11
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  int n;
  std::cin >> n;
  std::vector<int> beauty(n, 0);
  for (int p = 0; p < n; p++) {
    std::cin >> beauty[p];
  }
  sort(beauty.begin(), beauty.end());
  int count(1), maxCount(1);
  for (int p = 1; p < n; p++) {
    if (beauty[p] == beauty[p - 1]) {
      ++count;
    } else {
      count = 1;
    }
    maxCount = (count > maxCount) ? count : maxCount;
  }

  std::cout << (n - maxCount) << std::endl;

  return 0;
}
