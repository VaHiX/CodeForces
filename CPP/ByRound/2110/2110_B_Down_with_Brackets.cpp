/*
 * Problem URL : https://codeforces.com/problemset/problem/2110/B
 * Submit Date : 2025-08-10
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cnt(0);
    bool ans(true);
    for (int p = 1; p + 1 < s.size(); p++) {
      cnt += ((s[p] == '(') - (s[p] == ')'));
      if (cnt < 0) {
        ans = false;
      }
    }

    std::cout << (ans ? "NO" : "YES") << std::endl;
  }
}
