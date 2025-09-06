/*
 * Problem URL : https://codeforces.com/problemset/problem/2103/D
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
using pi = pair<int, int>;
const int N = 200005;
int n, a[N], v[N];
void solve() {
  cin >> n;
  vector<int> cur, nxt;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cur.push_back(i);
    if (a[i] == -1)
      a[i] = 0x3f3f3f3f;
  }
  int l = 1, r = n, idx = 1;
  while (cur.size() > 1) {
    nxt.clear();
    int pre = -1;
    for (int i = 0; i < cur.size(); i++) {
      int id = cur[i];
      if (a[id] > idx) {
        for (int j = pre + 1; j < i; j++)
          v[cur[j]] = ((idx & 1) ? r-- : l++);
        nxt.push_back(id);
        pre = i;
      }
    }
    for (int i = cur.size() - 1; i > pre; i--)
      v[cur[i]] = ((idx & 1) ? r-- : l++);
    idx += 1;
    swap(cur, nxt);
  }
  v[cur[0]] = l;
  for (int i = 1; i <= n; i++)
    cout << v[i] << " ";
  cout << '\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}