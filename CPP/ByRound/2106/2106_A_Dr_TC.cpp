/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/A
 * Submit Date : 2025-08-10
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(0);
    for (size_t p = 0; p < s.size(); p++) {
      cnt += (n - 2) * (s[p] == '1') + 1;
    }
    printf("%ld\n", cnt);
  }
}
