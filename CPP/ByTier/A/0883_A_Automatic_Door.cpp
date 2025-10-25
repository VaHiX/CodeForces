/*
 * Problem URL : https://codeforces.com/contest/883/problem/A
 * Submit Date : 2025-09-04
 */

#include <algorithm>
#include <bitset>
#include <ctype.h>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
typedef long long LL;
const LL inf = 3e18;
void gmin(LL &x, LL y) {
  if (y < x)
    x = y;
}
LL t[N];
LL n, A, m, D;
int main() {
  while (~scanf("%lld%lld%lld%lld", &n, &m, &A, &D)) {
    for (int i = 1; i <= m; ++i)
      scanf("%lld", &t[i]);
    sort(t + 1, t + m + 1);
    m = unique(t + 1, t + m + 1) - t - 1;
    t[m + 1] = inf; // 2e18

    LL p1 = 1, p2 = 1;

    LL num_in_D = D / A + 1;
    LL ans = 0;
    while (p1 <= n || p2 <= m) {
      LL now = inf;
      if (p1 <= n)
        gmin(now, p1 * A);
      if (p2 <= m)
        gmin(now, t[p2]);
      LL can = now + D;
      if (p2 <= m && t[p2] == now) {
        ++ans;
        p1 = can / A + 1;
        p2 = upper_bound(t + p2, t + m + 1, can) - t;
        //
        // printf("p2 first: p1 = %d p2 = %d\n", p1, p2);
        //
        continue;
      }
      p2 = upper_bound(t + p2, t + m + 1, can) - t;
      //
      // printf("p2=%d\n", p2);
      //
      LL ED = t[p2] - D - 1;
      LL lastp1 = min(ED / A, n);
      LL add = (lastp1 - p1 + 1 + num_in_D - 1) / num_in_D;

      //
      // printf("ED = %lld lastp1 = %lld add = %lld\n", ED, lastp1, add);
      //

      ans += add;
      p1 += add * num_in_D;

      //
      // getchar();
      //
    }
    printf("%lld\n", ans);
  }
  return 0;
}
/*
1 1 3 4
7

4 3 4 2
7 9 11

1000000000 0 1000000000 1000000000000000000

999999999 0 1000000000 1000000000

*/