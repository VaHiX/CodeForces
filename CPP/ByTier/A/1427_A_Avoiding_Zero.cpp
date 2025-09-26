/*
 * Problem URL : https://codeforces.com/problemset/problem/1427/A
 * Submit Date : 2025-08-14
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
    long total(0);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      total += a[p];
    }
    if (total == 0) {
      puts("NO");
      continue;
    }
    puts("YES");
    sort(a.begin(), a.end());
    long start(0), stop(n), step = 1;
    if (total > 0) {
      start = n - 1;
      stop = -1;
      step = -1;
    }
    for (long p = start; p != stop; p += step) {
      printf("%ld ", a[p]);
    }
    puts("");
  }

  return 0;
}
