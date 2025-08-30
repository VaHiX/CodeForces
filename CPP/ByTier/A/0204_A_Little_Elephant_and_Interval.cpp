/*
 * Problem URL : https://codeforces.com/problemset/problem/204/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

long long countSymmetric(long long x) {

  if (x < 10) {
    return x;
  }
  long long output = x / 10 + 9;
  long long msd(x), lsd(x % 10);
  while (msd >= 10) {
    msd /= 10;
  }
  if (msd > lsd) {
    --output;
  }
  return output;
}

int main() {

  long long l, r;
  scanf("%lld %lld\n", &l, &r);
  printf("%lld\n", countSymmetric(r) - countSymmetric(l - 1));
  return 0;
}
