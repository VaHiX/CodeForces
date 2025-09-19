/*
 * Problem URL : https://codeforces.com/contest/2026/problem/F
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 30000

int i, j, k, n, m, t, it, q;
int w1[N + 50], w2[N + 50], res[N + 50], fk[N + 50];
int cl[N + 50], cur, idx[N + 50];

vector<pair<int, int>> v[N + 50];
deque<int> q1;

struct SB {
#define md ((l + r) / 2)
#define ls (id * 2)
#define rs (ls + 1)
  basic_string<int> v[N * 4 + 50];
  int f[21][2005];
  void add(int id, int l, int r, int x, int y, int z) {
    if (x > y)
      return;
    if (x <= l && r <= y) {
      v[id] += z;
      return;
    }
    if (x <= md)
      add(ls, l, md, x, y, z);
    if (y > md)
      add(rs, md + 1, r, x, y, z);
  }
  void dfs(int id, int l, int r, int dep) {
    memcpy(f[dep], f[dep - 1], sizeof(f[dep]));
    for (auto x : v[id]) {
      for (int i = 2000; i >= w1[x]; i--)
        f[dep][i] = max(f[dep][i], f[dep][i - w1[x]] + w2[x]);
    }
    if (l == r) {
      res[idx[l]] = f[dep][fk[idx[l]]];
      return;
    }
    dfs(ls, l, md, dep + 1);
    dfs(rs, md + 1, r, dep + 1);
  }
} sb;

void dfs(int x) {
  basic_string<int> v1, v2;
  for (auto [op, y] : v[x]) {
    if (op == 1)
      dfs(y);
    else if (op == 2) {
      cl[y] = cur;
      q1.push_back(y);
      v1 += y;
    } else if (op == 3) {
      y = q1.front();
      q1.pop_front();
      sb.add(1, 1, q, cl[y] + 1, cur, y);
      v2 += y;
    } else if (op == 4)
      idx[++cur] = y;
  }
  reverse(v2.begin(), v2.end());
  for (auto i : v2) {
    cl[i] = cur;
    q1.push_front(i);
  }
  for (auto i : v1) {
    sb.add(1, 1, q, cl[i] + 1, cur, i);
    q1.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  it = 1;
  while (t--) {
    int op, x;
    cin >> op >> x;
    if (op == 1)
      v[x].push_back({1, ++it});
    else if (op == 2) {
      m++;
      cin >> w1[m] >> w2[m];
      v[x].push_back({2, m});
    } else if (op == 3)
      v[x].push_back({3, 0});
    else {
      cin >> fk[++q];
      v[x].push_back({4, q});
    }
  }
  dfs(1);
  sb.dfs(1, 1, q, 1);
  for (i = 1; i <= q; i++)
    cout << res[i] << '\n';
}