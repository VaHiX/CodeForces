/*
 * Problem URL : https://codeforces.com/problemset/problem/424/B
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
int siz, n, x, y, s, i;
pair<double, int> a[1005];
int main() {
  cin >> n >> siz;
  for (i = 0; i < n; i++) {
    cin >> x >> y >> s;
    a[i].first = sqrt(x * x + y * y);
    a[i].second = s;
  }
  sort(a, a + n);
  for (i = 0; i < n; i++) {
    siz = siz + a[i].second;
    if (siz >= 1000000) {
      printf("%16.10f", a[i].first);
      return 0;
    }
  }
  cout << -1;
}