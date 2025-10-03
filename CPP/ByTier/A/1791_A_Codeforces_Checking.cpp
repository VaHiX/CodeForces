/*
 * Problem URL : https://codeforces.com/problemset/problem/1791/A
 * Submit Date : 2025-08-13
 */

#include <iostream>

int main() {

  std::string target = "codeforces";
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::cout << ((target.find(s) != std::string::npos) ? "YES" : "NO")
              << std::endl;
  }
}
