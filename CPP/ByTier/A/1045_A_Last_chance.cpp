/*
 * Problem URL : https://codeforces.com/contest/1045/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>

#define x first

#define y second

#define m_p make_pair

using namespace std;

struct edge {

  short to, cap, rev;

  edge(int _a = 0, int _b = 0, int _c = 0) {

    to = _a;

    cap = _b;

    rev = _c;
  }
};

int S, T;

int dist[30010];

int cur[30010];

vector<edge> adj[30010];

int q[30010];

int hd, tl;

inline void addedge(int u, int v, int cap) {

  adj[u].push_back(edge(v, cap, adj[v].size()));

  adj[v].push_back(edge(u, 0, adj[u].size() - 1));
}

int dfs(int i, short fl) {

  if (i == T)
    return fl;

  short lf = fl;

  for (int &j = cur[i]; ~j; --j) {

    edge &e = adj[i][j];

    if (e.cap && dist[e.to] == dist[i] + 1) {

      short d = dfs(e.to, min(lf, e.cap));

      e.cap -= d;

      adj[e.to][e.rev].cap += d;

      lf -= d;

      if (!lf)
        return fl;
    }
  }

  dist[i] = -1;

  return fl - lf;
}

int Dinic() {

  int res = 0;

  while (true) {

    memset(dist, 0, sizeof(dist));

    dist[q[hd = tl = 0] = S] = 1;

    while (hd <= tl) {

      int i = q[hd++];

      cur[i] = adj[i].size() - 1;

      for (int j = cur[i]; ~j; --j) {

        edge &e = adj[i][j];

        if (e.cap && !dist[e.to]) {

          dist[e.to] = dist[i] + 1;

          q[++tl] = e.to;
        }
      }
    }

    if (!dist[T])
      break;

    int fl;

    while (fl = dfs(S, 10000))
      res += fl;
  }

  return res;
}

int bel[5010];

int tpe[5010];

int main(void) {

  int n, m;

  scanf("%d%d", &n, &m);

  S = 0;

  T = 30000;

  vector<pair<pair<int, int>, int>> v;

  for (int i = 1; i <= 8191; ++i) {

    addedge(n + i, n + (i << 1), 10000);

    addedge(n + i, n + (i << 1 | 1), 10000);
  }

  for (int i = 1; i <= n; ++i) {

    int a, b, c;

    scanf("%d%d", &tpe[i], &a);

    switch (tpe[i]) {

    case 0: {

      while (a--) {

        scanf("%d", &b);

        addedge(i, b + 8191 + n, 1);
      }

      break;
    }

    case 1: {

      scanf("%d", &b);

      v.push_back(m_p(m_p(a, b), i));

      int l = a + 8191, r = b + 8191;

      while (l <= r) {

        if (l & 1)
          addedge(i, n + l, 1), l++;

        if (!(r & 1))
          addedge(i, n + r, 1), r--;

        l >>= 1;

        r >>= 1;
      }

      break;
    }

    case 2: {

      scanf("%d%d", &b, &c);

      addedge(i, a + 8191 + n, 1);

      addedge(i, b + 8191 + n, 1);

      addedge(i, c + 8191 + n, 1);

      break;
    }
    }
  }

  sort(v.begin(), v.end());

  for (int i = 1; i <= n; ++i) {

    if (tpe[i] != 2) {

      addedge(S, i, 1);
    }
  }

  for (int i = 1; i <= n; ++i) {

    if (tpe[i] == 2) {

      addedge(S, i, 2);
    }
  }

  for (int i = 1; i <= m; ++i) {

    addedge(n + 8191 + i, T, 1);
  }

  printf("%d\n", Dinic());

  for (int i = 1; i <= m; ++i) {

    for (int j = adj[i + 8191 + n].size() - 1; ~j; --j) {

      edge &e = adj[i + 8191 + n][j];

      if (e.cap && e.to != T) {

        bel[i] = e.to;
      }
    }
  }

  multiset<pair<pair<int, int>, int>> s;

  int pnt = 0, vs = v.size();

  for (int i = 1; i <= m; ++i) {

    if (bel[i] <= n && tpe[bel[i]] != 1)
      continue;

    while (pnt < vs && v[pnt].x.x <= i) {

      s.insert(m_p(m_p(v[pnt].x.y, v[pnt].x.x), v[pnt].y));

      ++pnt;
    }

    while (!s.empty() && s.begin()->x.x < i)
      s.erase(s.begin());

    if (!s.empty())
      bel[i] = s.begin()->y, s.erase(s.begin());
  }

  for (int i = 1; i <= m; ++i) {

    if (bel[i])
      printf("%d %d\n", bel[i], i);
  }

  return 0;
}