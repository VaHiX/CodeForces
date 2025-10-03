/*
 * Problem URL : https://codeforces.com/contest/766/problem/D
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef long long ll;
typedef pair<int, bool> pi;
const int N = 1e5 + 1;
int n, m, q;
pi dsu[N];
unordered_map<string, int> mp;
pi find(int a) {
  if (dsu[a].f != a) {
    pi t = find(dsu[a].f);
    dsu[a] = {t.f, t.s ^ dsu[a].s};
  }
  return dsu[a];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    mp[s] = i;
    dsu[i] = {i, 0};
  }
  while (m--) {
    int parity;
    cin >> parity;
    parity--;
    string a, b;
    cin >> a >> b;
    pi c = find(mp[a]), d = find(mp[b]);
    if (c.f == d.f) {
      if ((c.s ^ d.s) == (bool)parity)
        cout << "YES\n";
      else
        cout << "NO\n";
    } else {
      cout << "YES\n";
      dsu[c.f] = {d.f, parity ^ c.s ^ d.s};
    }
  }
  while (q--) {
    string a, b;
    cin >> a >> b;
    pi c = find(mp[a]), d = find(mp[b]);
    if (c.f != d.f)
      cout << "3\n";
    else {
      if (c.s == d.s)
        cout << "1\n";
      else
        cout << "2\n";
    }
  }
}