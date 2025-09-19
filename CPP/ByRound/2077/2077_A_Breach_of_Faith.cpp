/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
int t, n, a[N], id;
long long ans[N];
void solve() {
  cin >> n;
  for (int i = 0; i < (n << 1); ++i)
    cin >> a[i];
  sort(a, a + (n << 1));
  long long res = 0;
  for (int i = 0; i < n - 1; ++i)
    res -= (ans[i << 1 | 1] = a[i]);
  for (int i = 0; i < n + 1; ++i)
    res += (ans[i << 1] = a[n + i - 1]);
  ans[(n << 1) - 1] = res;
  for (int i = 0; i <= (n << 1); ++i)
    cout << ans[i] << ' ';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--)
    solve(), cout << "\n";
  return 0;
}