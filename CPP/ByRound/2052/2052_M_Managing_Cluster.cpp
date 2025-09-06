/*
 * Problem URL : https://codeforces.com/problemset/problem/2052/M
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l, _ = r; i <= _; ++i)
#define per(i, r, l) for (int i = r, _ = l; i >= _; --i)
#define iter(x, v) for (int _p = head[x], v; v = ver[_p], _p; _p = nxt[_p])
#define ll long long
#define lowbit(x) ((x) & -(x))
template <typename T> inline void chkmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> inline void chkmax(T &x, T y) { x = x > y ? x : y; }
int t, n, bro[200010], pre[200010], ver[400010], nxt[400010], head[200010], num,
    a[200010], f[200010][2];
bool all[200010];
vector<pair<int, int>> ans, out;
vector<int> mp[200010];
void dfs(int x, int fa) {
  int sum0 = 0;
  iter(x, v) if (v != fa) dfs(v, x), sum0 += max(f[v][0], f[v][1]);
  f[x][0] = sum0;
  iter(x, v) if (v != fa) {
    int now = sum0 - max(f[v][0], f[v][1]) + f[v][0] + 1;
    if (now > f[x][1])
      f[x][1] = now, pre[x] = v;
  }
}
void dfs2(int x, int fa, int id) {
  if (!id || f[x][0] > f[x][1]) {
    iter(x, v) if (v != fa) dfs2(v, x, 1);
    return;
  }
  if (~pre[x])
    bro[x] = pre[x], bro[pre[x]] = x, ans.push_back(make_pair(x, pre[x])),
    dfs2(pre[x], x, 0);
  iter(x, v) if (v != fa && v != pre[x]) dfs2(v, x, 1);
}
inline void add(int x, int y) {
  ver[++num] = y, nxt[num] = head[x], head[x] = num;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    ans.clear(), out.clear(), num = 0;
    cin >> n, memset(head, 0, (2 * n + 1) << 2),
        memset(pre, 255, (2 * n + 1) << 2);
    memset(all, 0, 2 * n + 1), memset(bro, 0, (2 * n + 1) << 2);
    rep(i, 1, n) mp[i].clear();
    rep(i, 1, 2 * n) cin >> a[i], mp[a[i]].push_back(i);
    rep(i, 1, 2 * n - 1) {
      int x, y;
      cin >> x >> y;
      add(x, y), add(y, x);
    }
    rep(i, 1, 2 * n) f[i][0] = f[i][1] = 0;
    dfs(1, 0), dfs2(1, 0, 1);
    //		for(auto &p:ans) cout<<p.first<<' '<<p.second<<'\n';
    rep(i, 1, n) if (!all[i]) {
      if ((!bro[mp[i][0]] && !bro[mp[i][1]]) ||
          (bro[mp[i][0]] && bro[mp[i][1]]))
        continue;
      vector<int> S;
      S.clear();
      int X = mp[i][0];
      if (!bro[X])
        X = mp[i][1];
      while (true) {
        all[a[X]] = true;
        int nxtx = bro[X];
        S.push_back(X);
        //				cout<<X<<' '<<nxtx<<endl;
        int anox = mp[a[nxtx]][0] + mp[a[nxtx]][1] - nxtx;
        if (a[nxtx] == i)
          break;
        S.push_back(nxtx);
        //				cout<<anox<<' '<<bro[anox]<<endl;
        if (!bro[anox]) {
          all[a[nxtx]] = true, S.push_back(anox);
          break;
        }
        assert(!all[a[nxtx]]);
        X = anox;
      }
      int siz = S.size();
      //			for(auto &p:S) cout<<p<<' ';cout<<endl;
      rep(i, 0, siz / 2 - 1) out.push_back(make_pair(S[i], S[siz - i - 1]));
    }
    rep(i, 1, n) if (!all[i]) { // do it again
      if (!bro[mp[i][0]] || !bro[mp[i][1]])
        continue;
      vector<int> S;
      S.clear();
      int X = mp[i][0];
      if (!bro[X])
        X = mp[i][1];
      while (true) {
        all[a[X]] = true;
        int nxtx = bro[X];
        S.push_back(X);
        //				cout<<X<<' '<<nxtx<<endl;
        int anox = mp[a[nxtx]][0] + mp[a[nxtx]][1] - nxtx;
        if (a[nxtx] == i)
          break;
        S.push_back(nxtx);
        //				cout<<anox<<' '<<bro[anox]<<endl;
        if (!bro[anox]) {
          all[a[nxtx]] = true, S.push_back(anox);
          break;
        }
        assert(!all[a[nxtx]]);
        X = anox;
      }
      int siz = S.size();
      //			for(auto &p:S) cout<<p<<' ';cout<<endl;
      rep(i, 0, siz / 2 - 1) out.push_back(make_pair(S[i], S[siz - i - 1]));
    }
    cout << out.size() << '\n';
    for (auto &p : out)
      cout << p.first << ' ' << p.second << '\n';
  }
  cout << flush;
  return 0;
}
/*
3
2
1 2 2 1
1 2
2 3
3 4
4
4 3 1 3 2 4 1 2
1 2
3 1
3 4
5 1
5 6
2 7
2 8
3
1 1 2 2 3 3
1 2
1 3
1 4
1 5
1 6
*/
