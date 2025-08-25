/*
 * Problem URL : https://codeforces.com/problemset/problem/1717/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1717/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", n + 2 * (n / 2) + 2 * (n / 3));
  }
}
