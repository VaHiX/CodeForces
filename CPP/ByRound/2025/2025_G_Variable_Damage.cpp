/*
 * Problem URL : https://codeforces.com/contest/2025/problem/G
 * Submit Date : 2025-09-10
 */

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define MAXN 300005
const int B = 550;
#define ll long long
const int NB = (MAXN / B) + 5;

int n, X[MAXN];
struct Query {
  int op, pos;
} Q[MAXN];
int ord[MAXN], rev[MAXN];
int bel[MAXN], bl[NB], br[NB], nb;

int mx[NB], tag[NB], val[MAXN];
ll len[NB], d[MAXN], f[NB][B + 5];

int main() {
  ios::sync_with_stdio(false), cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> Q[i].op >> Q[i].pos, X[i] = Q[i].pos;
  iota(ord + 1, ord + 1 + n, 1);
  sort(ord + 1, ord + 1 + n, [&](int x, int y) { return Q[x].pos < Q[y].pos; });
  sort(X + 1, X + 1 + n);

  for (int i = 1; i <= n; i++)
    d[i] = X[i] - X[i - 1];
  for (int i = 1; i <= n; i++)
    rev[ord[i]] = i;

  for (int i = 1; i <= n; i += B) {
    ++nb;
    bl[nb] = i, br[nb] = min(i + B - 1, n);
    for (int j = bl[nb]; j <= br[nb]; j++)
      bel[j] = nb, len[nb] += d[j];
    for (int j = 1; j <= B; j++)
      f[nb][j] = j * len[nb];
  }

  ll sum = 0, res = 0;

  auto calc = [&](int bid) -> ll {
    if (mx[bid] < 0)
      return 0;
    if (mx[bid] > B)
      return f[bid][B] + len[bid] * (mx[bid] - B);
    return f[bid][mx[bid]];
  };

  auto update = [&](int bid, int k) {
    mx[bid] += k;
    tag[bid] += k;
  };

  auto build = [&](int bid) {
    int l = bl[bid], r = br[bid];
    mx[bid] = -1e9;
    for (int i = l; i <= r; i++) {
      val[i] += tag[bid];
      mx[bid] = max(mx[bid], val[i]);
    }
    tag[bid] = 0;

    fill(f[bid] + 0, f[bid] + B + 1, 0);
    for (int i = l; i <= r; i++) {
      int diff = mx[bid] - val[i];
      // assert(diff <= B);
      f[bid][diff + 1] += d[i];
    }
    for (int i = 1; i <= B; i++)
      f[bid][i] += f[bid][i - 1];
    for (int i = 1; i <= B; i++)
      f[bid][i] += f[bid][i - 1];
  };

  for (int i = 1; i <= n; i++) {
    if (Q[i].op == 1)
      sum += Q[i].pos;
    int bid = bel[rev[i]];
    int k = Q[i].op == 1 ? 1 : -1;
    for (int i = 1; i < bid; i++) {
      res -= calc(i);
      update(i, k);
      res += calc(i);
    }
    res -= calc(bid);
    for (int j = bl[bid]; j <= rev[i]; j++)
      val[j] += k;
    build(bid);
    res += calc(bid);
    // printf("sum = %lld, res = %lld\n", sum, res);
    cout << 2 * sum - res << '\n';
  }

  return 0;
}