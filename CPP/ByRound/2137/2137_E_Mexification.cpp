/*
 * Problem URL : https://codeforces.com/contest/2137/problem/E
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
long long a[200000], c[200001];
void solve(long long n) {
  long long i, cmex;
  for (i = 0; i <= n; i++)
    c[i] = 0;
  for (i = 0; i < n; i++)
    c[a[i]]++;
  cmex = -1;
  for (i = 0; i <= n; i++) {
    if (!c[i]) {
      cmex = i;
      break;
    }
  }
  for (i = 0; i < n; i++) {
    if (c[a[i]] == 1)
      a[i] = min(a[i], cmex);
    else
      a[i] = cmex;
  }
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  long long n, k, i, ans;
  for (cin >> T; T > 0; T--) {
    cin >> n >> k;
    for (i = 0; i < n; i++)
      cin >> a[i];
    if (k > 1)
      k = k % 2 + 2;
    for (i = 0; i < k; i++)
      solve(n);
    ans = 0;
    for (i = 0; i < n; i++)
      ans += a[i];
    cout << ans << '\n';
  }
  return 0;
}