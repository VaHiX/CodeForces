/*
 * Problem URL : https://codeforces.com/problemset/problem/1759/A
 * Submit Date : 2025-08-20
 */

#include <iostream>

int main() {

  const std::string pat = "Yes";

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;

    int shift(0);
    for (long p = 0; p < pat.size(); p++) {
      if (pat[p] == s[0]) {
        shift = p;
        break;
      }
    }

    bool ans(true);
    for (long p = 0; ans && p < s.size(); p++) {
      if (s[p] != pat[(p + shift) % 3]) {
        ans = false;
      }
    }

    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}
