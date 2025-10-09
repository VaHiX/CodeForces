/*
 * Problem URL : https://codeforces.com/contest/630/problem/J
 * Submit Date : 2025-09-08
 */

#include <iostream>
#include <vector>

int main() {

  const int64_t D = (2 * 2 * 2) * (3 * 3) * 5 * 7;
  int64_t n;
  std::cin >> n;
  std::cout << (n / D) << std::endl;

  return 0;
}
