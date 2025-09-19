/*
 * Problem URL : https://codeforces.com/contest/2028/problem/E
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 400000
#define M 998244353

ll i, j, k, n, m, t;
ll f[N + 50], dis[N + 50];
basic_string<int> v[N + 50];

ll ksm(ll a, ll p) {
  ll res = 1;
  while (p) {
    if (p & 1) {
      res = res * a % M;
    }
    a = a * a % M;
    p >>= 1;
  }
  return res;
}

void dfs1(int x, int fa) {
  dis[x] = 1e9;
  for (auto i : v[x])
    if (i != fa) {
      dfs1(i, x);
      dis[x] = min(dis[x], dis[i] + 1);
    }
  if (dis[x] > 1e8)
    dis[x] = 0;
}

void dfs2(int x, int fa) {
  if (x > 1) {
    f[x] = f[fa] * dis[x] % M * ksm(dis[x] + 1, M - 2) % M;
  }
  for (auto i : v[x])
    if (i != fa) {
      dfs2(i, x);
    }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 1; i < n; i++) {
      cin >> j >> k;
      v[j] += k;
      v[k] += j;
    }
    fill(f, f + n + 1, 0);
    f[1] = 1;
    dfs1(1, 0);
    dfs2(1, 0);

    for (i = 1; i <= n; i++) {
      cout << f[i] << ' ';
      v[i] = {};
    }
    cout << '\n';
  }
}