/*
 * Problem URL : https://codeforces.com/problemset/problem/1772/A
 * Submit Date : 2025-08-20
 */

#include <iostream>

int main() {

  int t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::cout << (s[0] - '0' + s[2] - '0') << std::endl;
  }
}
