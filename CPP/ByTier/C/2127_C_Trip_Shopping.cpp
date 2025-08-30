/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/C
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n;
array<int, 2> a[N];
void solve() {
  scanf("%d%*d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i][0]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i][1]);
  for (int i = 1; i <= n; i++)
    if (a[i][0] > a[i][1])
      swap(a[i][0], a[i][1]);
  sort(a + 1, a + n + 1);
  ll s = 0;
  for (int i = 1; i <= n; i++)
    s += a[i][1] - a[i][0];
  int delta = 1e9;
  for (int i = 1; i < n; i++)
    delta = min(delta, max(0, a[i + 1][0] - a[i][1]));
  s += 2 * delta;
  printf("%lld\n", s);
}
int main() {
  int Ncase;
  scanf("%d", &Ncase);
  while (Ncase--) {
    solve();
  }
}
