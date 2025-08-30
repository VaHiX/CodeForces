/*
 * Problem URL : https://codeforces.com/problemset/problem/2050/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    long x(0);
    for (long p = 0; p < n; p++) {
      std::string s;
      std::cin >> s;
      if (s.size() <= m) {
        x = p + 1;
        m -= s.size();
      } else {
        m = 0;
      }
    }

    std::cout << x << std::endl;
  }
}
