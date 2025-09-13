/*
 * Problem URL : https://codeforces.com/problemset/problem/2125/A
 * Submit Date : 2025-08-10
 */

#include <algorithm>
#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    sort(s.rbegin(), s.rend());
    std::cout << s << std::endl;
  }
}
