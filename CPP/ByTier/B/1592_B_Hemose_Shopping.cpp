/*
 * Problem URL : https://codeforces.com/contest/1592/problem/B
 * Submit Date : 2025-08-29
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      b[p] = a[p];
    }
    if (2 * x <= n) {
      puts("YES");
      continue;
    }
    sort(b.begin(), b.end());
    bool possible(true);
    for (long p = n - x; possible && p < x; p++) {
      if (a[p] != b[p]) {
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}
