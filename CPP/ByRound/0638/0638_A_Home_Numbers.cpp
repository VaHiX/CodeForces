/*
 * Problem URL : https://codeforces.com/contest/638/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>

int main() {

  long n, a;
  std::cin >> n >> a;
  long ans = 1 + ((a % 2) ? ((a - 1) / 2) : ((n - a) / 2));
  std::cout << ans << std::endl;

  return 0;
}
