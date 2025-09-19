/*
 * Problem URL : https://codeforces.com/problemset/problem/2082/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define Spc putchar(' ')
#define End putchar('\n')
#define For(i, il, ir) for (int i = (il); i <= (ir); ++i)
#define Fr(i, il, ir) for (int i = (il); i < (ir); ++i)
#define Forr(i, ir, il) for (int i = (ir); i >= (il); --i)
#define ForE(u) for (int i = head[u]; ~i; i = e[i].nxt)
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
namespace _TvT_ {
template <typename T> inline void rd(T &x) {
  bool f = 0;
  x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  if (f)
    x = -x;
}
template <typename T, typename... Args> void rd(T &first, Args &...args) {
  rd(first), rd(args...);
}
int write_num[50];
template <typename T> inline void write(T x) {
  int len = 0;
  if (x < 0)
    putchar('-'), x = -x;
  do
    write_num[len++] = x % 10;
  while (x /= 10);
  while (len--)
    putchar(write_num[len] + '0');
}
template <typename T, typename... Args> void write(T first, Args... args) {
  write(first), Spc, write(args...);
}
} // namespace _TvT_
using namespace _TvT_;
const int maxn = 1005;

int n, m;
int a[1005][1005];
int r[1005], c[1005];
vector<int> ver[4], vec[4];

vector<pii> rr, cc;

void upd(int i, int j, int v) { a[i][j] ^= v; }
void solve() {
  rd(n, m);
  For(i, 1, n) For(j, 1, m) {
    char ch = getchar();
    while (ch < '0' || ch > '3')
      ch = getchar();
    a[i][j] = ch - '0';
    r[i] ^= a[i][j], c[j] ^= a[i][j];
  }
  For(i, 1, n) ver[r[i]].pb(i);
  For(i, 1, m) vec[c[i]].pb(i);

  int ans = 0;
  For(i, 1, 3) ans += (int)ver[i].size() + (int)vec[i].size();
  For(i, 1, 3) while (!ver[i].empty() && !vec[i].empty()) {
    ans--;
    upd(ver[i].back(), vec[i].back(), i), ver[i].pop_back(), vec[i].pop_back();
  }
  For(x, 1, 3) if (!ver[x].empty()) For(y, x + 1, 3) if (!ver[y].empty()) {
    int z = x ^ y;
    if (vec[z].empty())
      continue;
    while (!ver[x].empty() && !ver[y].empty() && !vec[z].empty()) {
      ans--;
      upd(ver[x].back(), vec[z].back(), x);
      upd(ver[y].back(), vec[z].back(), y);
      ver[x].pop_back(), ver[y].pop_back(), vec[z].pop_back();
    }
  }
  For(x, 1, 3) if (!vec[x].empty()) For(y, x + 1, 3) if (!vec[y].empty()) {
    int z = x ^ y;
    if (ver[z].empty())
      continue;
    while (!vec[x].empty() && !vec[y].empty() && !ver[z].empty()) {
      ans--;
      upd(ver[z].back(), vec[x].back(), x);
      upd(ver[z].back(), vec[y].back(), y);
      ver[z].pop_back(), vec[x].pop_back(), vec[y].pop_back();
    }
  }
  For(x, 1, 3) if ((int)ver[x].size() > 1)
      For(y, 1, 3) if ((int)vec[y].size() > 1) while ((int)ver[x].size() > 1 &&
                                                      (int)vec[y].size() > 1) {
    ans--;
    int r1 = ver[x].back(), c1 = vec[y].back();
    ver[x].pop_back(), vec[y].pop_back();
    int r2 = ver[x].back(), c2 = vec[y].back();
    ver[x].pop_back(), vec[y].pop_back();
    upd(r1, c1, x);
    upd(r2, c1, x ^ y);
    upd(r2, c2, y);
  }
  For(x, 1, 3) for (int i : ver[x]) rr.pb(mk(i, x));
  For(x, 1, 3) for (int i : vec[x]) cc.pb(mk(i, x));

  if (!rr.empty() || !cc.empty()) {
    for (int i = 0; i < cc.size(); i++)
      upd(1, cc[i].fi, cc[i].se);
    for (int i = 0; i < rr.size(); i++)
      upd(rr[i].fi, 1, rr[i].se);
  }
  write(ans), End;
  For(i, 1, n) {
    For(j, 1, m) write(a[i][j]);
    End;
  }
}
void clear() {
  For(i, 1, n) r[i] = 0;
  For(i, 1, m) c[i] = 0;
  For(i, 0, 3) ver[i].clear(), vec[i].clear();
  rr.clear(), cc.clear();
}

signed main() {
  int T;
  rd(T);
  while (T--)
    solve(), clear();
  return 0;
}