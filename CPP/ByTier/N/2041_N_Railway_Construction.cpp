// Problem: CF 2041 N - Railway Construction
// https://codeforces.com/contest/2041/problem/N

/*
Algorithm: Minimum Spanning Tree (MST) with modifications
Approach:
1. For each possible prison location u, we compute the minimum cost to connect all other states
2. The prison state u is isolated from all others (no edges connected to u)
3. The rest of the states form a connected MST with minimum total cost
4. We use a modified version of Kruskal's algorithm to find the minimum cost
5. Key steps:
   - For each possible prison location u, build a spanning tree for all other nodes
   - The cost of each edge is a[u] + a[v] (fee to states u and v)
   - Some edges may be blocked (no construction possible)
   - Use a greedy approach to build the MST with minimum total cost

Time Complexity: O(n^2 * log(n)) where n is number of states
Space Complexity: O(n^2) for storing edges and auxiliary data structures
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

#define int ll
#define m_p(a, b) make_pair(a, b)
#define pb push_back
#define ll long long
#define ull unsigned long long
#define ld long double
#define inf 0x7FFFFFFF
#define inff 9223372036854775807
#define rep(i, l, r) for (int i = l; i < r; ++i)
#define repp(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r - 1; i >= l; --i)
#define pper(i, r, l) for (int i = r; i >= l; --i)
#define pii pair<int, int>
#define fi first
#define se second
#define p_q priority_queue
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)
#define lb(x) ((x) & -(x))
#define lg(x) (31 ^ __builtin_clz(x))
#define vi vector<int>
#define vii vector<pii>
#define vT vector<T>
#define mm1 mint(1)
const int mod = 998244353;
const int intsz = sizeof(int);
using namespace std;
inline int rd() {
  int x(0), f(1);
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -f;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}
inline void out(int X) {
  if (X < 0) {
    X = ~(X - 1);
    putchar('-');
  }
  if (X > 9)
    out(X / 10);
  putchar(X % 10 + '0');
}
ll pw(ll x, int d) {
  ll t = 1;
  for (; d; d >>= 1, x = x * x % mod)
    if (d & 1)
      t = t * x % mod;
  return t;
}
#define MAX 200005
#define A 1505
int a[MAX];
pii b[MAX];
vector<int> v[MAX];
int ans[MAX];
int num[MAX];
int prmnum[MAX];
int n, m;
int pa[MAX];
int col[MAX];
vector<int> colv[MAX];
array<int, 3> w[A][A];
array<int, 3> dis[MAX];
bool block[MAX];
bool intree[MAX];
vector<int> G[MAX];
int colcnt;
int solve(int ban) {
  int rlt = 0;
  colcnt = 0;
  memset(prmnum, 0, sizeof(prmnum));
  memset(pa, 0, sizeof(pa));
  memset(col, 0, sizeof(col));
  memset(intree, 0, sizeof(intree));
  memset(w, 0x3f, sizeof(w));
  rep(i, 0, A) colv[i].clear();
  int st = 1;
  if (ban == 1)
    st++;
  repp(i, st, n) {
    if (i == ban)
      continue;
    int p = 0;
    for (auto to : v[i]) {
      if (to == ban)
        continue;
      ++p;
      if (p == ban)
        ++p;
      if (p >= i)
        break;
      if (p != to) {
        pa[i] = p;
        col[i] = col[p];
        rlt += a[i] + a[p];
        break;
      }
    }
    if (!pa[i]) {
      ++p;
      if (p == ban)
        ++p;
      if (p < i) {
        pa[i] = p;
        col[i] = col[p];
        rlt += a[i] + a[p];
      }
    }
    if (!pa[i]) {
      col[i] = ++colcnt;
      prmnum[colcnt] = i;
    }
    colv[col[i]].pb(i);
  }
  repp(i, 1, n) {
    if (i == ban)
      continue;
    for (auto to : v[i])
      block[to] = 1;
    rep(j, 1, col[i]) {
      for (auto itm : colv[j]) {
        if (!block[itm]) {
          if (col[i] >= A) {
            cout << "?? " << col[i] << ' ' << colcnt << ' ' << ban << endl;
            exit(0);
          }
          if (j >= A) {
            cout << "?? " << j << ' ' << colcnt << ' ' << ban << endl;
            exit(0);
          }
          w[col[i]][j] = min(w[col[i]][j], {a[itm] + a[i], i, itm});
          w[j][col[i]] = min(w[col[i]][j], {a[itm] + a[i], i, itm});
          break;
        }
      }
    }
    for (auto to : v[i])
      block[to] = 0;
  }
  int lst = 1;
  memset(dis, 0x3f, sizeof(dis));
  repp(_, 1, colcnt - 1) {
    intree[lst] = 1;
    pair<int, int> nxt = {inff / 2, inff / 2};
    repp(j, 1, colcnt) {
      if (intree[j])
        continue;
      dis[j] = min(dis[j], w[lst][j]);
      nxt = min(nxt, {dis[j][0], j});
    }
    if (nxt.fi > inff / 16)
      return -1;
    rlt += nxt.fi;
    lst = nxt.se;
  }
  return rlt;
}
void adde(int x, int y) {
  G[x].pb(y);
  G[y].pb(x);
}
signed main() {
  n = rd();
  m = rd();
  repp(i, 1, n) b[i] = {rd(), i};
  vii tmpe;
  repp(i, 1, m) {
    int x = rd();
    int y = rd();
    tmpe.pb({x, y});
  }
  if (n == 2) {
    repp(i, 1, n) cout << 0 << ' ';
    return 0;
  }
  sort(b + 1, b + 1 + n);
  repp(i, 1, n) num[b[i].se] = i, a[i] = b[i].fi;
  for (auto itm : tmpe) {
    int x = num[itm.fi];
    int y = num[itm.se];
    v[x].pb(y);
    v[y].pb(x);
  }
  repp(i, 1, n) sort(all(v[i]));
  int tot = solve(0);
  if (tot == -1) {
    int idx = 0;
    repp(i, 1, n) ans[i] = -1;
    repp(i, 1, n) {
      if (v[i].size() == n - 1) {
        ans[i] = solve(i);
        break;
      }
    }
    repp(i, 1, n) cout << ans[num[i]] << ' ';
    cout << endl;
    return 0;
  }
  repp(i, 1, n) {
    if (pa[i])
      adde(pa[i], i);
  }
  repp(i, 2, colcnt) { adde(dis[i][1], dis[i][2]); }
  repp(i, 1, n) {
    if (G[i].size() == 1) {
      ans[i] = tot - a[G[i][0]] - a[i];
      continue;
    }
    ans[i] = solve(i);
  }
  repp(i, 1, n) { cout << ans[num[i]] << ' '; }
  cout << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/