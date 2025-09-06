/*
 * Problem URL : https://codeforces.com/problemset/problem/1312/B
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1312/B
 * Submit Date : 2025-08-22
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
    sort(a.rbegin(), a.rend());
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }

  return 0;
}
