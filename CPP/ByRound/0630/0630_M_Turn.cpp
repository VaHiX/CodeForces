/*
 * Problem URL : https://codeforces.com/contest/630/problem/M
 * Submit Date : 2025-09-08
 */

#include <iostream>

int main() {

  const int64_t C = 360;
  int64_t x;
  std::cin >> x;
  x %= C;
  if (x < 0) {
    x += C;
  }
  int ans(0), min(C + 1);
  for (int p = 0; p < 5; p++) {
    int64_t y = (C + x - 90 * p) % C;
    if (y < min) {
      min = y;
      ans = p;
    }
    if ((C - y) < min) {
      min = C - y;
      ans = p;
    }
  }

  ans %= 4;
  std::cout << ans << std::endl;

  return 0;
}
