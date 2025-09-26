/*
 * Problem URL : https://codeforces.com/problemset/problem/1566/B
 * Submit Date : 2025-08-22
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool nz(0), na(0);
    int ans(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '0') {
        ans = 1;
        if (nz && na) {
          ans = 2;
          break;
        }
        nz = true;
      } else if (s[p] == '1' && nz) {
        na = true;
      }
    }

    printf("%d\n", ans);
  }
}
