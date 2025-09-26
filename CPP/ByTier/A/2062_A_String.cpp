/*
 * Problem URL : https://codeforces.com/problemset/problem/2062/A
 * Submit Date : 2025-08-08
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long ones(0);
    for (char x : s) {
      ones += (x == '1');
    }
    std::cout << ones << std::endl;
  }
}
