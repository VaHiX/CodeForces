/*
 * Problem URL : https://codeforces.com/contest/2041/problem/I
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define maxn 2000010
using namespace std;
using ll = long long;
int tot = 0, fa[maxn];
map<int, int> son[maxn];
string s[maxn];
priority_queue<int, vector<int>, greater<int>> trie[maxn];
int res[maxn];
bool vis[maxn];
void pushup(int x) {
  int mx = 0, id = -1;
  for (auto [i, y] : son[x]) {
    if (res[y] != -1 && s[res[y]].size() > mx) {
      mx = s[res[y]].size();
      id = res[y];
    }
  }
  if (id == -1 && trie[x].size())
    id = trie[x].top();
  if (id != res[x]) {
    res[x] = id;
    if (x)
      pushup(fa[x]);
  }
}
void add(string &t, int id) {
  int p = 0, len = t.size();
  for (int i = 0; i < len; i++) {
    char c = t[i] - 33;
    if (son[p].find(c) == son[p].end()) {
      son[p][c] = ++tot;
      fa[tot] = p;
    }
    p = son[p][c];
  }
  trie[p].push(id);
  pushup(p);
}
void del(string &t) {
  int p = 0, len = t.size();
  for (int i = 0; i < len; i++) {
    char c = t[i] - 33;
    p = son[p][c];
  }
  while (!trie[p].empty() && vis[trie[p].top()])
    trie[p].pop();
  pushup(p);
}
void solve() {
  int n;
  cin >> n;
  int now = 0;
  memset(res, -1, sizeof(res));
  while (n--) {
    string opt;
    cin >> opt;
    if (opt == "add") {
      int id;
      cin >> id;
      cin >> s[id];
      add(s[id], id);
    } else if (opt == "delete") {
      int id;
      cin >> id;
      vis[id] = 1;
      del(s[id]);
    } else if (opt == "append") {
      string t;
      cin >> t;
      for (auto c : t) {
        c -= 33;
        if (son[now].find(c) == son[now].end()) {
          son[now][c] = ++tot;
          fa[tot] = now;
        }
        now = son[now][c];
      }
    } else if (opt == "backspace") {
      int t;
      cin >> t;
      while (now && t--)
        now = fa[now];
    }
    cout << res[now] << '\n';
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  // cin>>T;
  while (T--)
    solve();
  return 0;
}