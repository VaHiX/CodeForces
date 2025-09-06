/*
 * Problem URL : https://codeforces.com/problemset/problem/1819/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _ = 5e5 + 5;
ll N, n, t, l, r, a[_], i;
bool f;
map<ll, ll> b, c;
void P() {
  cin >> n;
  b.clear();
  c.clear();
  for (i = 1; i <= n; i++)
    cin >> a[i], b[a[i]]++;
  for (t = 0; b[t]; t++)
    ;
  for (l = n + 1, r = 0, i = 1; i <= n; i++)
    if (a[i] == t + 1)
      l = min(l, i), r = max(r, i);
  for (i = l; i <= r; i++)
    c[a[i]]++;
  for (f = (t < n), i = 0; i < t; i++)
    if (c[i] == b[i])
      f = 0;
  cout << (f ? "Yes\n" : "No\n");
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  while (N--)
    P();
}