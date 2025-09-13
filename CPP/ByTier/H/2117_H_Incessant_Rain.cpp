/*
 * Problem URL : https://codeforces.com/problemset/problem/2117/H
 * Submit Date : 2025-08-14
 */

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
typedef long long ll;

const int N = 3e5, M = N * 20;
int t, n, q, a[N + 1];

struct Node {
  int c, ls, rs, ms;
  int l, r;
};

int trees[N + 1];
Node nodes[M + 1];
vector<int> av;

void freenode(int &ci) {
  av.push_back(ci);
  ci = 0;
}

void update(int i, int x, int l, int r, int &ci) {
  if (!ci) {
    ci = av.back();
    av.pop_back();
  }
  auto &cur = nodes[ci];

  if (l == r) {
    cur.c = cur.ls = cur.rs = cur.ms = x;
    if (!x)
      freenode(ci);
    return;
  }

  int m = (l + r) / 2;
  if (i <= m)
    update(i, x, l, m, cur.l);
  else
    update(i, x, m + 1, r, cur.r);

  int lt = m - l + 1, rt = r - m;
  auto &ln = nodes[cur.l], &rn = nodes[cur.r];
  cur.c = ln.c + rn.c;
  cur.ls = max(ln.ls, 2 * ln.c - lt + rn.ls);
  cur.rs = max(rn.rs, 2 * rn.c - rt + ln.rs);
  cur.ms = max({ln.ms, rn.ms, ln.rs + rn.ls});
  if (!cur.c)
    freenode(ci);
}

void destroy(int &ci) {
  if (!ci)
    return;
  auto &cur = nodes[ci];
  freenode(ci);
  destroy(cur.l);
  destroy(cur.r);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  av.reserve(M);
  for (int i = 1; i <= M; i++)
    av.push_back(i);

  cin >> t;
  while (t--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      update(i, 1, 1, n, trees[a[i]]);
    }

    priority_queue<int> ans;
    vector<int> m(n + 1);
    for (int i = 1; i <= n; i++)
      ans.push(nodes[trees[i]].ms);

    while (q--) {
      int i, x;
      cin >> i >> x;

      auto f = [&](int x) {
        int &ci = trees[a[i]];
        auto &node = nodes[ci];
        m[node.ms]++;
        update(i, x, 1, n, ci);
        ans.push(node.ms);
      };

      f(0), a[i] = x, f(1);
      while (m[ans.top()]) {
        m[ans.top()]--;
        ans.pop();
      }
      cout << ans.top() / 2 << " ";
    }
    cout << endl;

    for (int i = 1; i <= n; i++)
      destroy(trees[i]);
  }
}