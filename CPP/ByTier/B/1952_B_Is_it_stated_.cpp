/*
 * Problem URL : https://codeforces.com/problemset/problem/1952/B
 * Submit Date : 2025-08-12
 */

#include <iostream>
#include <string>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::cout << (s.find("it") != std::string::npos ? "YES" : "NO")
              << std::endl;
  }
}
