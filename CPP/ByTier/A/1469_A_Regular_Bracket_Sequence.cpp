/*
 * Problem URL : https://codeforces.com/contest/1469/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1469/A
 * Submit Date : 2025-08-23
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    puts((s[0] == ')' || s[s.size() - 1] == '(' || s.size() % 2) ? "NO"
                                                                 : "YES");
  }
}
