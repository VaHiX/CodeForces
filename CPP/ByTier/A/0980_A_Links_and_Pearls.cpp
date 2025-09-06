/*
 * Problem URL : https://codeforces.com/contest/980/problem/A
 * Submit Date : 2025-08-31
 */



#include <iostream>

int main() {

  std::string s;
  std::cin >> s;
  long x(0), y(0);
  for (long p = 0; p < s.size(); p++) {
    x += (s[p] == 'o');
    y += (s[p] == '-');
  }

  std::cout << (((x == 0) || (y % x == 0)) ? "YES" : "NO") << std::endl;

  return 0;
}
