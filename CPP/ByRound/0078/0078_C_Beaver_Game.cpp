/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>

int main() {

  long n, m, k;
  scanf("%ld %ld %ld\n", &n, &m, &k);
  if (n % 2 == 0) {
    puts("Marsel");
    return 0;
  } else {
    bool possible(0);
    for (long p = 1; p * p <= m; p++) {
      if (m % p > 0) {
        continue;
      }
      if ((k <= (m / p) && p > 1) || ((k <= p) && (m / p > 1))) {
        possible = 1;
        break;
      }
    }

    puts(possible ? "Timur" : "Marsel");
  }

  return 0;
}
