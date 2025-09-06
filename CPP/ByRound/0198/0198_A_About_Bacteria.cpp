/*
 * Problem URL : https://codeforces.com/problemset/problem/198/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
int main() {
  long long k, b, n, t;
  std::cin >> k >> b >> n >> t;
  for (long long s = k + b; s <= t && n > 0; s = k * s + b, --n)
    ;
  std::cout << n;
}
