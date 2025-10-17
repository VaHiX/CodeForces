/*
 * Problem URL : https://codeforces.com/contest/1065/problem/A
 * Submit Date : 2025-08-31
 */

#include <iostream>
long long a, b, c, s;
main() {
  std::cin >> a;
  while (std::cin >> s >> a >> b >> c)
    std::cout << s / c + s / c / a * b << "\n";
}