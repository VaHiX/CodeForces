/*
 * Problem URL : https://codeforces.com/problemset/problem/1926/B
 * Submit Date : 2025-08-12
 */

#include <iostream>

int main() {

  std::ios_base::sync_with_stdio(false);

  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    bool triangle(true);
    long prev(0);
    for (long row = 0; row < n; row++) {
      std::string s;
      std::cin >> s;
      long ones(0);
      for (long col = 0; col < s.size(); col++) {
        ones += (s[col] == '1');
      }
      if (ones > 0 && prev > 0 && ones == prev) {
        triangle = false;
      }
      prev = ones;
    }

    std::cout << (triangle ? "TRIANGLE" : "SQUARE") << std::endl;
  }
}
