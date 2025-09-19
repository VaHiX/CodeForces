/*
 * Problem URL : https://codeforces.com/contest/2002/problem/F1
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e7 + 10;
const int MAXM = 2e3 + 10;

int pr[MAXN], tot;
bool v[MAXN];

inline void init(int n) {
  v[0] = v[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!v[i])
      pr[++tot] = i;
    for (int j = 1; j <= tot && i * pr[j] <= n; j++) {
      v[i * pr[j]] = 1;
      if (i % pr[j] == 0)
        break;
    }
  }
}

int n, m, p, q;

inline ll f(int x, int y) {
  ll res = (ll)x * p + (ll)y * q;
  if (y <= n)
    res = max(res, (ll)x * q + (ll)y * p);
  return res;
}

bool vis[MAXM][MAXM], res;
ll ans;

vector<pair<int, int>> tmp;

void dfs(int x, int y) {
  if (__gcd(x, y) > 1)
    return;
  ans = max(ans, f(x, y));
  vis[n - x][m - y] = 1, tmp.emplace_back(x, y);
  if (x < n && !vis[n - x - 1][m - y])
    dfs(x + 1, y);
  if (res)
    return;
  if (y == m)
    return res = 1, void();
  if (y < m && !vis[n - x][m - y - 1])
    dfs(x, y + 1);
  if (res)
    return;
}

int T, x, y;

int main() {
  for (init(2e7), scanf("%d", &T); T--;) {
    scanf("%d%d%d%d", &n, &m, &p, &q);
    ans = res = 0;
    for (y = m; v[y]; y--)
      ;
    for (x = min(n, y - 1); !res; x--) {
      ans = max(ans, f(x, y));
      if (y < m)
        dfs(x, y + 1);
      else
        break;
    }
    for (auto [i, j] : tmp)
      vis[n - i][m - j] = 0;
    tmp.clear();
    printf("%lld\n", ans);
  }
}