/*
 * Problem URL : https://codeforces.com/problemset/problem/1760/B
 * Submit Date : 2025-08-20
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long mx(0);
    for (long p = 0; p < n; p++) {
      long x = s[p] - 'a';
      mx = (mx > x) ? mx : x;
    }

    std::cout << (mx + 1) << std::endl;
  }
}
