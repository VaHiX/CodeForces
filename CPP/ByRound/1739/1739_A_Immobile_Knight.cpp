/*
 * Problem URL : https://codeforces.com/problemset/problem/1739/A
 * Submit Date : 2025-08-21
 */

#include <iostream>
int main() {
  int t, a;
  std::cin >> t;
  for (t *= 2; t--;) {
    std::cin >> a;
    std::cout << (a + 1) / 2 << '\n';
  }
}