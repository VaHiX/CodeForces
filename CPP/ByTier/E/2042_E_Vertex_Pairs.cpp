/*
 * Problem URL : https://codeforces.com/contest/2042/problem/E
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 2e5 + 5;
int col[N << 1];
int sc[N << 1];
int tmp1[N];
struct et {
  int to, nxt;
} e[N << 2];
int head[N << 1], ecnt;
void addedge(int u, int v) {
  e[++ecnt] = et{v, head[u]};
  head[u] = ecnt;
}
int fp[N << 1], lp[N << 1];
int dfncnt;
#define y e[i].to
int qzr_maxl[N << 1];
int fa[N << 1];
void dfs1(int x, int father) {
  fa[x] = father;
  fp[x] = ++dfncnt;
  qzr_maxl[dfncnt] = qzr_maxl[dfncnt - 1];
  if (tmp1[col[x]]) {
    qzr_maxl[dfncnt] = max(qzr_maxl[dfncnt], tmp1[col[x]]);
  } else {
    tmp1[col[x]] = dfncnt;
  }
  for (int i = head[x]; i; i = e[i].nxt) {
    if (y == father) {
      continue;
    }
    dfs1(y, x);
  }
  lp[x] = dfncnt;
}
int used[N << 1];
void pick(int x) {
  if (x == 0 || used[x] != 0) {
    return;
  }
  used[x] = 1;
  pick(fa[x]);
}
void erase(int x) {
  if (used[x] != 0) {
    return;
  }
  used[x] = -1;
  pick(sc[x]);
  for (int i = head[x]; i; i = e[i].nxt) {
    if (y == fa[x]) {
      continue;
    }
    erase(y);
  }
}
void work(int rt) {
  for (int i = 1; i <= n; ++i) {
    tmp1[i] = 0;
  }
  for (int i = 1; i <= n << 1; ++i) {
    used[i] = 0;
  }
  dfncnt = 0;
  qzr_maxl[0] = 0;
  dfs1(rt, 0);
  for (int i = n << 1; i; --i) {
    if (used[i] != 0) {
      continue;
    }
    if (fp[i] <= qzr_maxl[lp[i]]) {
      pick(i);
    } else {
      erase(i);
    }
  }
}
bool ans1[N << 1], ans2[N << 1];
int ans1cnt, ans2cnt;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n << 1; ++i) {
    cin >> col[i];
    if (tmp1[col[i]]) {
      sc[i] = tmp1[col[i]];
      sc[tmp1[col[i]]] = i;
    } else {
      tmp1[col[i]] = i;
    }
  }
  int rt1 = tmp1[1];
  ecnt = 1;
  int inp1, inp2;
  for (int i = 1; i < n << 1; ++i) {
    cin >> inp1 >> inp2;
    addedge(inp1, inp2);
    addedge(inp2, inp1);
  }
  ans1cnt = ans2cnt = 0;
  work(rt1);
  for (int i = 1; i <= n << 1; ++i) {
    ans1[i] = (used[i] == 1);
    ans1cnt += (used[i] == 1);
  }
  rt1 = sc[rt1];
  work(rt1);
  for (int i = 1; i <= n << 1; ++i) {
    ans2[i] = (used[i] == 1);
    ans2cnt += (used[i] == 1);
  }
  bool *ans = ans1;
  int anscnt = ans1cnt;
  for (int i = n << 1; i; --i) {
    if (ans1[i] == ans2[i]) {
      continue;
    }
    if (ans1[i]) {
      ans = ans2;
      anscnt = ans2cnt;
    } else {
      ans = ans1;
      anscnt = ans1cnt;
    }
    break;
  }
  cout << anscnt << "\n";
  for (int i = 1; i <= n << 1; ++i) {
    if (ans[i]) {
      cout << i << " ";
    }
  }
  return 0;
} // SongShouqian , 2024/12/19 17:05