/*
 * Problem URL : https://codeforces.com/problemset/problem/1935/A
 * Submit Date : 2025-08-12
 */

#include <algorithm>
#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string rev(s);
    std::reverse(rev.begin(), rev.end());
    std::string a(s), b(rev + s);
    std::cout << (a < b ? a : b) << std::endl;
  }
}
