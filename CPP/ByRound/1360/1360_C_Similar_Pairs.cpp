/*
 * Problem URL : https://codeforces.com/contest/1360/problem/C
 * Submit Date : 2025-08-26
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());
    bool odds(true), nxt(false);
    for (long p = 0; p < n; p++) {
      if (a[p] & 1) {
        odds = !odds;
      }
      if (p > 0 && a[p] == a[p - 1] + 1) {
        nxt = true;
      }
    }

    puts((odds || nxt) ? "YES" : "NO");
  }

  return 0;
}
