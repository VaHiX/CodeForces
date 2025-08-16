/*
 * Problem URL : https://codeforces.com/problemset/problem/2121/C
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <set>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> f(n, std::vector<long>(m, 0));
    long mx(0);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &f[row][col]);
        mx = (mx > f[row][col] ? mx : f[row][col]);
      }
    }

    std::vector<long> vr(n), vc(m);
    long mxcnt(0);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        if (f[row][col] < mx) {
          continue;
        }
        ++vr[row];
        ++vc[col];
        ++mxcnt;
      }
    }

    bool single(false);
    for (long row = 0; !single && row < n; row++) {
      for (long col = 0; !single && col < m; col++) {
        single |= ((vr[row] + vc[col] - (f[row][col] == mx)) == mxcnt);
      }
    }

    printf("%ld\n", mx - single);
  }
}
