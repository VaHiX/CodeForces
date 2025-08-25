/*
 * Problem URL : https://codeforces.com/problemset/problem/1335/D
 * Submit Date : 2025-08-14
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    for (long p = 0; p < 9; p++) {
      std::string s;
      std::cin >> s;
      for (long p = 0; p < 9; p++) {
        if (s[p] == '1') {
          s[p] = '2';
        }
      }
      std::cout << s << std::endl;
    }
  }

  return 0;
}
