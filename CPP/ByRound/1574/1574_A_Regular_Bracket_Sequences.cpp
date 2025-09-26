/*
 * Problem URL : https://codeforces.com/problemset/problem/1574/A
 * Submit Date : 2025-08-23
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a(n, '('), b(n, ')');
    std::string s(a + b);
    std::cout << s << std::endl;
    for (long p = 0; p + 1 < n; p++) {
      std::string x(s);
      x[n - 1] = ')';
      x[n + p] = '(';
      std::cout << x << std::endl;
    }
  }
}
