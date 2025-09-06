/*
 * Problem URL : https://codeforces.com/problemset/problem/2084/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k;
void solve() {
  scanf("%d%d%d", &n, &m, &k);
  int x = max(n / (m + 1), k);
  for (int i = 0; i < n; i++)
    cout << i % x << " ";
  cout << "\n";
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}