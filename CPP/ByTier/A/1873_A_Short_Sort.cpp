/*
 * Problem URL : https://codeforces.com/problemset/problem/1873/A
 * Submit Date : 2025-08-15
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::cout << ((s == "bca" || s == "cab") ? "NO" : "YES") << std::endl;
  }
}
