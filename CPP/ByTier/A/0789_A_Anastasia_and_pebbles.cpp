/*
 * Problem URL : https://codeforces.com/problemset/problem/789/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/789/A
 * Submit Date : 2025-08-22
 */

#include <cstdio>

int main() {

  long n, k;
  scanf("%ld %ld", &n, &k);
  long total(0);
  while (n--) {
    long x;
    scanf("%ld", &x);
    total += (x / k) + (x % k > 0);
  }
  long days = (total / 2) + (total % 2);
  printf("%ld\n", days);

  return 0;
}
