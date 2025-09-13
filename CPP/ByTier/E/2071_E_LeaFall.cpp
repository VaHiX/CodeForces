/*
 * Problem URL : https://codeforces.com/problemset/problem/2071/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

#include <chrono>
#include <random>
using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define eb emplace_back
#define endl '\n'
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vll vector<ll>
#define pll pair<ll, ll>
#define pii pair<int, int>
#define vpii vector<pii>
#define vpll vector<pll>
#define vvpi vector<vpii>
#define Yes cout << "YES" << endl;
#define No cout << "NO" << endl;
const ll MOD = 998244353;
// const int MOD = 1000000007;

vi line[100000];
ll p[100000], dp[100000][4][3], tdp[4][3];

ll qpow(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1)
      ans = ans * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return ans;
}

void dfs(int t, int f) {
  vi::iterator it;
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++)
      dp[t][i][j] = 0;
  }
  dp[t][0][0] = p[t];
  dp[t][1][0] = (1 + MOD - p[t]) % MOD;
  dp[t][2][1] = (1 + MOD - p[t]) % MOD;
  for (it = line[t].begin(); it != line[t].end(); it++) {
    if (*it == f)
      continue;
    dfs(*it, t);
    for (i = 0; i <= 2; i++) {
      for (j = 0; i + j <= 2; j++) {
        tdp[0][i + j] =
            (tdp[0][i + j] +
             dp[t][0][i] * (dp[*it][0][j] + dp[*it][1][j] + dp[*it][3][j])) %
            MOD;
        tdp[1][i + j] =
            (tdp[1][i + j] +
             dp[t][1][i] * (dp[*it][0][j] + dp[*it][1][j] + dp[*it][2][j])) %
            MOD;
        tdp[2][i + j] = (tdp[2][i + j] + dp[t][2][i] * dp[*it][0][j]) % MOD;
        tdp[3][i + j] = (tdp[3][i + j] + dp[t][3][i] * dp[*it][0][j]) % MOD;
        tdp[3][i + j] =
            (tdp[3][i + j] + dp[t][2][i] * (dp[*it][1][j] + dp[*it][2][j])) %
            MOD;
      }
    }
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 3; j++) {
        dp[t][i][j] = tdp[i][j];
        tdp[i][j] = 0;
      }
    }
  }
}

void solve() {
  int n, i, u, v;
  ll a, b;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> a >> b;
    p[i] = a * qpow(b, MOD - 2) % MOD;
  }
  for (i = 0; i < n - 1; i++) {
    cin >> u >> v;
    line[u - 1].pb(v - 1);
    line[v - 1].pb(u - 1);
  }
  dfs(0, -1);
  cout << (dp[0][0][2] + dp[0][1][2] + dp[0][3][2]) % MOD << endl;
  for (i = 0; i < n; i++)
    line[i].clear();
}

int32_t main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
