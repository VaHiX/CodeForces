/*
 * Problem URL : https://codeforces.com/problemset/problem/774/C
 * Submit Date : 2025-08-21
 */

#include <iostream>

int main() {

  long n;
  std::cin >> n;
  std::string s("");
  for (long p = 0; p < n / 2; p++) {
    s += '1';
  }
  if (n & 1) {
    s[0] = '7';
  }
  std::cout << s << std::endl;

  return 0;
}
