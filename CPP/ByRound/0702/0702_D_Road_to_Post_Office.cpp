/*
 * Problem URL : https://codeforces.com/contest/702/problem/D
 * Submit Date : 2025-09-02
 */

#include <algorithm>
#include <iostream>

int main() {

  int64_t d, k, a, b, t;
  std::cin >> d >> k >> a >> b >> t;

  if (d <= k) {
    std::cout << (d * a) << std::endl;
  } else {
    d -= k;
    std::cout << (k * a + (d / k) * std::min(k * a + t, k * b) +
                  std::min(t + (d % k) * a, (d % k) * b))
              << std::endl;
  }

  return 0;
}
