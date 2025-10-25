/*
 * Problem URL : https://codeforces.com/problemset/problem/1602/A
 * Submit Date : 2025-08-23
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    char mn('z');
    long minPos(-1);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] <= mn) {
        mn = s[p];
        minPos = p;
      }
    }
    std::string a(1, mn), b("");
    for (long p = 0; p < s.size(); p++) {
      if (p == minPos) {
        continue;
      }
      b = b + s[p];
    }

    std::cout << a << " " << b << std::endl;
  }
}
