/*
 * Problem URL : https://codeforces.com/contest/1401/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1401/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long res = (k > n) ? (k - n) : ((2 + (n - k) % 2) % 2);
    printf("%ld\n", res);
  }

  return 0;
}
