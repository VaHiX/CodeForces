/*
 * Problem URL : https://codeforces.com/contest/519/problem/C
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/519/problem/C
 * Submit Date : 2025-09-02
 */

#include <algorithm>
#include <cstdio>
#include <iostream>

int main() {

  long a, b;
  std::cin >> a >> b;
  if (b < a) {
    long temp = a;
    a = b;
    b = temp;
  }

  long ans(0);
  for (int p = 0; p <= a && 2 * p <= b; p++) {
    long test = p + std::min(b - 2 * p, (a - p) / 2);
    if (test > ans) {
      ans = test;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
