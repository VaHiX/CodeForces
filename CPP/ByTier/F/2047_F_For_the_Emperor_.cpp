/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5, I = 1e9;

int Tc, n, m, a[N];

struct Fl {
  struct E {
    int to, val, nxt, cst;
  } e[N];

  int S, T = 1e4, t = 1, h[N], v[N], dis[N], inc[N], p[N], mf, r;

  void A(int x, int y, int v, int c = 0) {
    e[++t].to = y;
    e[t].val = v;
    e[t].nxt = h[x];
    e[t].cst = c;
    h[x] = t;
    e[++t].to = x;
    e[t].val = 0;
    e[t].nxt = h[y];
    e[t].cst = -c;
    h[y] = t;
  }

  int SPFA() {
    memset(v, 0, sizeof(v));
    fill(dis, dis + N, I);
    fill(inc, inc + N, I);
    queue<int> q;
    q.push(S);
    v[S] = 1;
    dis[S] = 0;
    for (int x; q.size(); q.pop()) {
      x = q.front();
      v[x] = 0;
      for (int i = h[x]; i; i = e[i].nxt) {
        int y = e[i].to;
        if (e[i].val > 0 && dis[x] + e[i].cst < dis[y]) {
          dis[y] = dis[x] + e[i].cst;
          inc[y] = min(inc[x], e[i].val);
          p[y] = i;
          if (!v[y]) {
            q.push(y);
            v[y] = true;
          }
        }
      }
    }
    return dis[T] < 1e9;
  }

  void U() {
    int cur = T;
    for (; cur != S;) {
      int lst = p[cur];
      e[lst].val -= inc[T];
      e[lst ^ 1].val += inc[T];
      cur = e[lst ^ 1].to;
    }
    mf += inc[T];
    r += dis[T] * inc[T];
    return;
  }

  void G() {
    for (; SPFA();) {
      U();
    }
  }
} fl, f_;

struct Sd {
  int v[N], d[N], t[N], u, o[N], s[N], c, w[N], b[N];
  vector<int> e[N];
  stack<int> k;

  void T(int x) {
    d[x] = t[x] = ++u;
    v[x] = o[x] = 1;
    k.push(x);
    for (int i : e[x]) {
      if (!v[i]) {
        T(i);
        t[x] = min(t[x], t[i]);
      } else if (o[i]) {
        t[x] = min(t[x], d[i]);
      }
    }
    if (d[x] == t[x]) {
      s[x] = ++c;
      o[x] = 0;
      b[c] = 1;
      w[c] = a[x];
      for (; k.top() != x; s[k.top()] = c, o[k.top()] = 0, k.pop()) {
        w[c] += a[k.top()];
        b[c]++;
      }
      k.pop();
    }
  }
} gr, g_;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  for (cin >> Tc; Tc--; fl = f_, gr = g_) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1, u, v; i <= m; i++) {
      cin >> u >> v;
      gr.e[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
      if (!gr.v[i]) {
        gr.T(i);
      }
    }
    for (int i = 1; i <= gr.c; i++) {
      fl.A(fl.S, i + n, gr.w[i]);
      fl.A(i, i + n, 1, -1);
      fl.A(i + n, i + 2 * n, I);
      fl.A(i + 2 * n, fl.T, I);
    }
    for (int i = 1; i <= n; i++) {
      for (int j : gr.e[i]) {
        if (gr.s[i] != gr.s[j]) {
          fl.A(gr.s[i] + 2 * n, gr.s[j], 1);
          fl.A(gr.s[i] + 2 * n, gr.s[j] + n, I);
        }
      }
    }
    for (int i = 1; i <= gr.c; i++) {
      fl.A(i + n, i + 2 * n, 1, -1e6);
    }
    fl.G();
    if (fl.r <= -(int)1e6 * gr.c) {
      cout << fl.r + (int)1e6 * gr.c + gr.c << '\n';
    } else {
      cout << "-1\n";
    }
  }
  return 0;
}