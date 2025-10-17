/*
 * Problem URL : https://codeforces.com/contest/1512/problem/E
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, i, l, r, s, a[501], b[501], j;
int main() {
  scanf("%d", &t);
  for (; t > 0; t--) {
    memset(b, 0, sizeof(b));
    memset(a, 0, sizeof(a));
    scanf("%d%d%d%d", &n, &l, &r, &s);
    if (s < (1 + (r - l + 1)) * (r - l + 1) / 2 ||
        s > (n + n - r + l) * (r - l + 1) / 2) {
      cout << -1 << endl;
      continue;
    }
    for (i = n; i > 0 && s != 0; i--)
      if (s - i >= (1 + r - l) * (r - l) / 2 && s >= i)
        s -= i, a[l++] = i, b[i] = 1;
    for (i = 1, j = 1; i <= n; i++)
      if (b[i] == 0) {
        while (a[j] != 0)
          j++;
        a[j++] = i;
      }
    for (i = 1; i <= n; i++)
      cout << a[i] << " ";
    cout << endl;
  }
  return 0;
}