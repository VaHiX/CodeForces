/*
 * Problem URL : https://codeforces.com/contest/2029/problem/G
 * Submit Date : 2025-09-09
 */

#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define pb push_back

typedef long long ll;
typedef long double ld;
int n;
int m;
int V;
const int maxN = 2e5 + 10;
ll c[maxN];
const int maxP = 2005;
// 2005 * 2e5 *
ll dp[maxP][maxP];
ll d[maxN];
int prv[maxP];
ll f[maxP];
mt19937 rnd(228);
inline void umax(ll &a, const ll b) { a = max(a, b); }
void solve() {

  cin >> n >> m >> V;
  //    n = rnd() % 20 + 1;
  //    m = rnd() % 20 + 1;
  //    V = rnd() % 5 + 1;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
    //        c[i] = rnd() % 10000 + 1;
    d[i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    char c;
    cin >> c;
    //        if (rnd() % 2) c = 'L';
    //        else c = 'R';
    int x;
    cin >> x;
    //        x = rnd() % n + 1;
    if (c == 'L') {
      d[1] += 1;
      d[x + 1] -= 1;
    } else {
      d[x] += 1;
    }
  }
  int sz = 1;
  for (int i = 1; i <= n; i++) {
    d[i] += d[i - 1];
  }
  for (int i = 2; i <= n; i++) {
    if (d[i] == d[sz]) {
      c[sz] += c[i];
    } else {
      sz++;
      assert(sz <= i);
      d[sz] = d[i];
      c[sz] = c[i];
    }
  }
  n = sz;
  for (int i = 0; i <= V; i++) {
    for (int j = 0; j <= V; j++) {
      dp[i][j] = -1e18;
    }
  }
  for (int i = 0; i <= V; i++) {
    prv[i] = -1;
  }
  int op = 0;
  //    cout << m << endl;
  //    for (int i = 1; i <= n; i++) cout << d[i] << " ";
  //    cout << endl;
  for (int i = 1; i <= n; i++) {
    assert(op <= m + n);
    if (d[i] <= V) {
      int mx = -1;
      for (int j = 0; j <= V; j++) {
        f[j] = -1e18;
      }
      f[d[i]] = c[i];
      for (int x = d[i]; x >= 0; x--) {
        if (mx < prv[x]) {
          ++op;
          mx = prv[x];
          for (int S = x; S + d[i] - x <= V; S++) {
            umax(f[S + d[i] - x], dp[S][x] + c[i]);
          }
        }
      }
      mx = prv[d[i]];
      for (int x = d[i] + 1; x <= V; x++) {
        if (mx < prv[x]) {
          ++op;
          mx = prv[x];
          for (int S = x; S <= V; S++) {
            f[S] = max(f[S], dp[S][x] + c[i]);
          }
        }
      }
      prv[d[i]] = i;
      for (int x = d[i]; x <= V; x++)
        dp[x][d[i]] = f[x];
    }
  }
  ll mx = 0;
  for (int x = 0; x <= V; x++) {
    for (int y = 0; y <= V; y++) {
      umax(mx, dp[x][y]);
      //            mx = max(mx, dp[x][y]);
    }
    if (x != 0)
      cout << mx << " ";
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef DEBUG
  freopen("input.txt", "r", stdin);
#endif
  int tst = 10000;
  cin >> tst;
  while (tst--)
    solve();
  return 0;
}