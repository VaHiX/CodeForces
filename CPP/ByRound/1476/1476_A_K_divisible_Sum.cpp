/*
 * Problem URL : https://codeforces.com/contest/1476/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1476/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (n <= k) {
      printf("%ld\n", (k + n - 1) / n);
    } else {
      printf("%d\n", 1 + (n % k > 0));
    }
  }
}
