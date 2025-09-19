/*
 * Problem URL : https://codeforces.com/problemset/problem/2084/H
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 1000000007;
const int N = 2100000;
int a[N], w[N], dp[N], dp2[N], o[N][2], oo[N][2], ooo[N][2];
void solve(int _, int n) {
  dp[n] = dp2[n] = 1;
  dp2[n + 1] = 0;
  dp2[n + 2] = 0;
  dp[n + 1] = dp[n + 2] = 0;
  if (n & 1)
    ooo[0][0] = n + 2, ooo[0][1] = n + 1;
  else
    ooo[0][0] = n + 1, ooo[0][1] = n + 2;
  int tot[2] = {}, ans[2] = {};
  for (int i = n - 1; i >= _; i--) {
    while (tot[i & 1] && w[i] + (ooo[tot[i & 1]][i & 1] - i - 1) / 2 >=
                             oo[tot[i & 1]][i & 1]) {
      int k = tot[i & 1];
      ans[i & 1] -= ((ll)dp[ooo[k][i & 1]] * (oo[k][i & 1] - o[k][i & 1]) +
                     dp2[ooo[k][i & 1]] - dp2[ooo[k - 1][i & 1]]) %
                    p;
      ans[i & 1] = (p + ans[i & 1] % p) % p;
      tot[i & 1]--;
    }
    int t = w[i] + (ooo[tot[i & 1]][i & 1] - i - 1) / 2;
    if (tot[i & 1])
      ans[i & 1] -=
          (ll)dp[ooo[tot[i & 1]][i & 1]] * (t - o[tot[i & 1]][i & 1]) % p;
    ans[i & 1] = (p + ans[i & 1] % p) % p;
    o[tot[i & 1]][i & 1] = t;
    int k = (++tot[i & 1]);
    o[k][i & 1] = 1;
    ooo[k][i & 1] = i + 1;
    oo[k][i & 1] = w[i];
    ans[i & 1] += ((ll)dp[ooo[k][i & 1]] * (oo[k][i & 1] - o[k][i & 1]) +
                   dp2[ooo[k][i & 1]] - dp2[ooo[k - 1][i & 1]]) %
                  p;
    ans[i & 1] = (p + ans[i & 1] % p) % p;
    dp[i] = ans[i & 1];
    if ((i & 1) == (n & 1))
      dp[i] = (dp[i] + 1) % p;
    //        cout<<i<<" "<<dp[i]<<"\n";
    dp2[i] = (dp2[i + 2] + dp[i]) % p;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int _;
  cin >> _;
  while (_--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 1; i <= n; i++)
      a[i] = s[i - 1] - '0';
    a[n + 1] = -1;
    int tot = 0;
    for (int i = 2, pre = 1; i <= n + 1; i++) {
      if (a[i] != a[pre])
        w[++tot] = i - pre, pre = i;
    }
    if (tot == 1) {
      cout << w[1] - 1 << "\n";
      continue;
    }
    solve(2, tot);
    int ans = ((ll)(w[1] - 1) * dp[2] + dp2[2] + dp2[3]) % p;
    cout << (ll)ans * w[tot] % p << "\n";
  }
  return 0;
}