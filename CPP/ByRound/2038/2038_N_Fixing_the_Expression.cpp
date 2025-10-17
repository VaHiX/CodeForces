/*
 * Problem URL : https://codeforces.com/problemset/problem/2038/N
 * Submit Date : 2025-08-10
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    if (s[0] < s[2]) {
      s[1] = '<';
    } else if (s[0] > s[2]) {
      s[1] = '>';
    } else if (s[0] == s[2]) {
      s[1] = '=';
    }
    std::cout << s << std::endl;
  }
}
