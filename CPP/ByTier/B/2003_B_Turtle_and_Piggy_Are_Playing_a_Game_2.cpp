/*
 * Problem URL : https://codeforces.com/problemset/problem/2003/B
 * Submit Date : 2025-08-08
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
    printf("%ld\n", a[n / 2]);
  }
}
