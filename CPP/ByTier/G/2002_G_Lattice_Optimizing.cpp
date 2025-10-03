/*
 * Problem URL : https://codeforces.com/contest/2002/problem/G
 * Submit Date : 2025-09-14
 */

#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ll long long

const int N = 21;

int T, n, m, k, ans;
int d[N][N], r[N][N];
ll h;
struct HashTable {
  static const int M = 1 << 26, P = 3e7 + 1;
  int tot;
  int head[P], nxt[M];
  ll val[M];
  vector<int> had;
  il void Clear() {
    for (auto v : had)
      head[v] = 0;
    tot = 0, had.clear();
    return;
  }
  il void Insert(ll x) {
    int p = x % P;
    for (int i = head[p]; i; i = nxt[i]) {
      if (val[i] == x)
        return;
    }
    if (!head[p])
      had.push_back(p);
    nxt[++tot] = head[p], head[p] = tot, val[tot] = x;
    return;
  }
  il bool Find(ll x) {
    int p = x % P;
    for (int i = head[p]; i; i = nxt[i]) {
      if (val[i] == x)
        return true;
    }
    return false;
  }
} mp;

il void Dfs1(int x, int y, int t, ll S) {
  if (t == k) {
    for (ll T = S; T; T = (T - 1) & S)
      mp.Insert(((ll)x << 40) | T);
    return;
  }
  if (x < n)
    Dfs1(x + 1, y, t + 1, S | (1ll << d[x][y]));
  if (y < n)
    Dfs1(x, y + 1, t + 1, S | (1ll << r[x][y]));
  return;
}
il void Dfs2(int x, int y, int t, ll S) {
  if (t == k) {
    while (mp.Find(((ll)x << 40) | (~S & h)))
      ans++, h |= 1ll << ans;
    return;
  }
  if (x > 1)
    Dfs2(x - 1, y, t - 1, S | (1ll << d[x - 1][y]));
  if (y > 1)
    Dfs2(x, y - 1, t - 1, S | (1ll << r[x][y - 1]));
  return;
}

il void Build() {
  cin >> n, m = (n - 1) << 1, k = m / 3;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= n; j++)
      cin >> d[i][j];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < n; j++)
      cin >> r[i][j];
  }
  ans = 0, h = 1, mp.Clear();
  for (int i = 1; i <= n; i++)
    mp.Insert((ll)i << 40);
  Dfs1(1, 1, 0, 0), Dfs2(n, n, m, 0);
  cout << ans << "\n";
  return;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    Build();
  return 0;
}