/*
 * Problem URL : https://codeforces.com/problemset/problem/1420/C1
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1420/C1
 * Submit Date : 2025-08-22
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, q;
    scanf("%ld %ld", &n, &q);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long long f(a[0]), g(0);
    for (long p = 1; p < n; p++) {
      f = std::max(f, std::max(g + a[p], 0LL));
      g = std::max(g, f - a[p]);
    }

    printf("%lld\n", std::max(f, g));
  }
}
