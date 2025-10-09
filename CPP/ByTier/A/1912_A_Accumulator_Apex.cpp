/*
 * Problem URL : https://codeforces.com/problemset/problem/1912/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int, int> PII;
const int N = 2e5 + 5, mod = 998244353;
int T, x, k;
void solve() {
  cin >> x >> k;
  vector<PII> q;
  for (int i = 0, n; i < k; i++) {
    cin >> n;
    int minv = 0, last = 0, sum = 0;
    for (int j = 0, y; j < n; j++) {
      cin >> y;
      sum += y;
      minv = max(minv, -sum);
      if (sum > last)
        q.push_back({minv, sum - last}), last = sum;
    }
  }
  sort(q.begin(), q.end());
  for (auto t : q)
    if (x >= t.first)
      x += t.second;
  cout << x << endl;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
}
