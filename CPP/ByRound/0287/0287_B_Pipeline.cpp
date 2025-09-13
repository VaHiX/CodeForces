/*
 * Problem URL : https://codeforces.com/contest/287/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long long n(0), k(0);
  scanf("%lld %lld", &n, &k);

  if (n == 1) {
    puts("0");
  } else if (n <= k) {
    puts("1");
  } else if (n > k * (k - 1) / 2 + 1) {
    puts("-1");
  } else {

    long long lowerBound(1), upperBound(k - 1), mid(1);
    long long subtr = 1 + k * (k - 1) / 2;
    long long test = subtr - (mid * (mid - 1)) / 2;

    while (lowerBound + 1 < upperBound) {
      mid = (lowerBound + upperBound) / 2;
      test = subtr - (mid * (mid - 1)) / 2;

      if (test == n) {
        upperBound = mid;
        break;
      } else if (test > n) {
        lowerBound = mid;
      } else if (test < n) {
        upperBound = mid;
      }
    }

    long long output(0);
    if (test < n) {
      output = k - mid + 1;
    } else if (test >= n) {
      output = k - mid;
    }

    printf("%lld\n", output);
  }

  return 0;
}
