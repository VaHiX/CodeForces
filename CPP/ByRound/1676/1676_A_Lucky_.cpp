/*
 * Problem URL : https://codeforces.com/problemset/problem/1676/A
 * Submit Date : 2025-08-17
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long t(0);
    for (long p = 0; p < 6; p++) {
      t += (p < 3 ? -1 : 1) * (s[p] - '0');
    }
    std::cout << (t ? "NO" : "YES") << std::endl;
  }
}
