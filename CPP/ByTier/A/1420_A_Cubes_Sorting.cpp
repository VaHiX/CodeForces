/*
 * Problem URL : https://codeforces.com/contest/1420/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1420/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long last(-1);
    bool ans(false);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p && (x >= last)) {
        ans = true;
      }
      last = x;
    }

    puts(ans ? "YES" : "NO");
  }

  return 0;
}
