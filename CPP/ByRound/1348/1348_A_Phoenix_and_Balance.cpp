/*
 * Problem URL : https://codeforces.com/contest/1348/problem/A
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
main() {
  int t, n;
  for (std::cin >> t; t--;) {
    std::cin >> n, std::cout << 2 * (pow(2, n / 2) - 1) << '\n';
  }
}