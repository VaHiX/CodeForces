/*
 * Problem URL : https://codeforces.com/problemset/problem/2102/D
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define N 200005
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, i, a[N], p[N], x, y, j, k;
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    for (i = 1; i <= n; i++)
      p[a[i]] = i;
    x = y = 0;
    j = 1;
    k = 2;
    for (i = 1; i <= n; i++) {
      if (p[i] % 2) {
        if (p[i] != j)
          x ^= 1;
        p[a[j]] = p[i];
        swap(a[p[i]], a[j]);
        p[i] = j;
        j += 2;
      } else {
        if (p[i] != k)
          y ^= 1;
        p[a[k]] = p[i];
        swap(a[p[i]], a[k]);
        p[i] = k;
        k += 2;
      }
    }
    if (x ^ y)
      swap(a[n], a[n - 2]);
    for (i = 1; i <= n; i++)
      cout << a[i] << ' ';
    cout << '\n';
  }
  return 0;
}
