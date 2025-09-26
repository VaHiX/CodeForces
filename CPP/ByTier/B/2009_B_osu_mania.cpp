/*
 * Problem URL : https://codeforces.com/problemset/problem/2009/B
 * Submit Date : 2025-08-10
 */

#include <iostream>
#include <vector>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      std::string s;
      std::cin >> s;
      for (long u = 0; u < 4; u++) {
        if (s[u] == '#') {
          v[p] = u + 1;
          break;
        }
      }
    }

    for (long p = n - 1; p >= 0; p--) {
      std::cout << v[p] << " ";
    }
    std::cout << std::endl;
  }
}
