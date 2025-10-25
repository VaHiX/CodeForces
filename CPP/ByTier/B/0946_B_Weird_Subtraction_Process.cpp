/*
 * Problem URL : https://codeforces.com/problemset/problem/946/B
 * Submit Date : 2025-08-23
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll a, b;
  scanf("%lld %lld", &a, &b);

  while (true) {
    if (a >= 2 * b) {
      ll d = (a - b) / (2 * b);
      a -= d * 2 * b;
      if (a >= 2 * b) {
        a -= 2 * b;
      }
    }

    if (a <= 0 || b <= 0) {
      break;
    }

    if (b >= 2 * a) {
      ll d = (b - a) / (2 * a);
      b -= d * 2 * a;
      if (b >= 2 * a) {
        b -= 2 * a;
      }
    }

    if (a <= 0 || b <= 0) {
      break;
    }
    if ((a < 2 * b) && (b < 2 * a)) {
      break;
    }
  }

  printf("%lld %lld\n", a, b);

  return 0;
}
