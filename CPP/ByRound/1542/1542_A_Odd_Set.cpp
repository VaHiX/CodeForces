/*
 * Problem URL : https://codeforces.com/problemset/problem/1542/A
 * Submit Date : 2025-08-19
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1542/A
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    for (long p = 0; p < 2 * n; p++) {
      long x;
      scanf("%ld", &x);
      cnt += (x % 2);
    }

    puts(cnt == n ? "Yes" : "No");
  }
}
