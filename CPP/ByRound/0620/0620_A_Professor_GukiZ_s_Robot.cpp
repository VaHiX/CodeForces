/*
 * Problem URL : https://codeforces.com/problemset/problem/620/A
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <iostream>

int main() {

  long x1, y1;
  std::cin >> x1 >> y1;
  long x2, y2;
  std::cin >> x2 >> y2;
  std::cout << std::max(std::abs(x1 - x2), std::abs(y1 - y2)) << std::endl;

  return 0;
}
