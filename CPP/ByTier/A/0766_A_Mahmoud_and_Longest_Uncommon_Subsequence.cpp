/*
 * Problem URL : https://codeforces.com/problemset/problem/766/A
 * Submit Date : 2025-08-13
 */

#include <iostream>

int main() {

  std::string s, t;
  std::cin >> s >> t;
  if (s == t) {
    std::cout << "-1" << std::endl;
  } else {
    std::cout << ((s.size() > t.size()) ? s.size() : t.size()) << std::endl;
  }

  return 0;
}
