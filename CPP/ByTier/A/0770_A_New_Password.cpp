/*
 * Problem URL : https://codeforces.com/contest/770/problem/A
 * Submit Date : 2025-09-01
 */

#include <iostream>

int main() {

  int n, k;
  std::cin >> n >> k;
  std::string s;
  for (int p = 0; p < n; p++) {
    s += 'a' + (p % k);
  }
  std::cout << s << std::endl;

  return 0;
}
