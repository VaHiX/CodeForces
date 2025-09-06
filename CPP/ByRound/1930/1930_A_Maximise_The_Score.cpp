/*
 * Problem URL : https://codeforces.com/problemset/problem/1930/A
 * Submit Date : 2025-08-12
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
    std::vector<long> a(2 * n);
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());
    long sum(0);
    for (long p = 0; p < 2 * n; p += 2) {
      sum += a[p];
    }
    printf("%ld\n", sum);
  }
}
