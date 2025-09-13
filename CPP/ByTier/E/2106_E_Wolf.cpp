/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/E
 * Submit Date : 2025-08-17
 */

#include <algorithm>
#include <stdio.h>
using namespace std;

int n, q, a[200020], c[200020];

void solve() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    c[a[i]] = i;
  }
  while (q--) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    if (c[k] < l || r < c[k]) {
      printf("-1 ");
      continue;
    }
    int ta = 0, tb = 0, tc = 0, td = 0;
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (mid == c[k])
        break;
      if (mid < c[k]) {
        ta += a[mid] > k;
        tc += a[mid] < k;
        l = mid + 1;
      } else {
        tb += a[mid] < k;
        td += a[mid] > k;
        r = mid - 1;
      }
    }
    if (ta >= k - tc || n - tb < k + td) {
      printf("-1 ");
      continue;
    }
    printf("%d ", max(ta, tb) * 2);
  }
  putchar('\n');
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}