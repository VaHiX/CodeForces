/*
 * Problem URL : https://codeforces.com/contest/1480/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1480/A
 * Submit Date : 2025-08-23
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    for (long p = 0; p < s.size(); p++) {
      if (p % 2) {
        s[p] = (s[p] != 'z' ? 'z' : 'y');
      } else {
        s[p] = (s[p] != 'a' ? 'a' : 'b');
      }
    }

    std::cout << s << std::endl;
  }
}
