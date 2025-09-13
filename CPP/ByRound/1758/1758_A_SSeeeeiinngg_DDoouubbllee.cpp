/*
 * Problem URL : https://codeforces.com/problemset/problem/1758/A
 * Submit Date : 2025-08-20
 */

#include <algorithm>
#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::cout << s;
    reverse(s.begin(), s.end());
    std::cout << s << std::endl;
  }
}
