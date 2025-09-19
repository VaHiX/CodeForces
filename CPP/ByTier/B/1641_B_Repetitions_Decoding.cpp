/*
 * Problem URL : https://codeforces.com/problemset/problem/1641/B
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

int t, n;
vector<int> vec;
vector<int> ans;
int cidx;
vector<pair<int, int>> ops;

void solve() {
  cin >> n;
  vec.resize(n);
  for (int &e : vec)
    cin >> e;
  ops.clear();
  ans.clear();
  cidx = 0;
  while (!vec.empty()) {
    cidx++;
    auto it = find(vec.begin() + 1, vec.end(), vec.front());
    if (it == vec.end()) {
      cout << "-1\n";
      return;
    }
    cidx += it - vec.begin();
    ans.push_back(it - vec.begin());
    for (auto e = ++vec.begin(); e != it; e++)
      ops.emplace_back(cidx++, *e);
    reverse(vec.begin() + 1, it);
    vec.erase(it);
    vec.erase(vec.begin());
  }
  cout << ops.size() << '\n';
  for (auto e : ops)
    cout << e.first << ' ' << e.second << '\n';
  cout << ans.size() << '\n';
  for (int e : ans)
    cout << e * 2 << ' ';
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> t;
  while (t--)
    solve();
}