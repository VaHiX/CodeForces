/*
 * Problem URL : https://codeforces.com/problemset/problem/1626/A
 * Submit Date : 2025-08-15
 */

#include <algorithm>
#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    sort(s.begin(), s.end());
    std::cout << s << std::endl;
  }
}
