/*
 * Problem URL : https://codeforces.com/contest/832/problem/A
 * Submit Date : 2025-08-31
 */

#include <iostream>

int main() {

  int64_t n, k;
  std::cin >> n >> k;
  int64_t win = (n / k) % 2;
  std::cout << (win ? "YES" : "NO") << std::endl;

  return 0;
}
