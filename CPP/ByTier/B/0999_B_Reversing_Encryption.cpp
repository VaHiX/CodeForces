/*
 * Problem URL : https://codeforces.com/problemset/problem/999/B
 * Submit Date : 2025-08-15
 */

#include <algorithm>
#include <iostream>

int main() {

  long n;
  scanf("%ld", &n);
  std::string s;
  std::cin >> s;
  for (long p = 2; p <= n; p++) {
    if (n % p > 0) {
      continue;
    }
    std::reverse(s.begin(), s.begin() + p);
  }

  std::cout << s << std::endl;

  return 0;
}
