/*
 * Problem URL : https://codeforces.com/problemset/problem/1837/C
 * Submit Date : 2025-08-18
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    if (s[0] == '?') {
      s[0] = '0';
    }
    for (long p = 1; p < s.size(); p++) {
      if (s[p] == '?') {
        s[p] = s[p - 1];
      }
    }
    std::cout << s << std::endl;
  }
}
