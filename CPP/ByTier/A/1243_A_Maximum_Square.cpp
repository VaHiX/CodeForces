/*
 * Problem URL : https://codeforces.com/contest/1243/problem/A
 * Submit Date : 2025-08-27
 */



#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.rbegin(), a.rend());
    long side(0);
    for (long p = 0; p < n; p++) {
      if (a[p] >= p + 1) {
        side = p + 1;
      } else {
        break;
      }
    }

    printf("%ld\n", side);
  }

  return 0;
}
