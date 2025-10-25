/*
 * Problem URL : https://codeforces.com/contest/919/problem/B
 * Submit Date : 2025-09-12
 */

#include <cstdio>

bool isPerfect(long x) {
  int s(0);
  while (x > 0) {
    s += (x % 10);
    x /= 10;
  }
  return (s == 10);
}

int main() {

  long k;
  scanf("%ld", &k);

  long cnt(0);
  for (long p = 1; p < 1e9; p++) {
    if (!isPerfect(p)) {
      continue;
    }
    ++cnt;
    if (cnt == k) {
      printf("%ld\n", p);
      break;
    }
  }

  return 0;
}
