/*
 * Problem URL : https://codeforces.com/problemset/problem/1922/A
 * Submit Date : 2025-08-12
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a, b, c;
    std::cin >> a >> b >> c;
    bool res(false);
    for (long p = 0; !res && p < n; p++) {
      if (c[p] != a[p] && c[p] != b[p]) {
        res = true;
      }
    }

    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}
