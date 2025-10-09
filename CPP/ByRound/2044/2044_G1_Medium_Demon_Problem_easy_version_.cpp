/*
 * Problem URL : https://codeforces.com/contest/2044/problem/G1
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 7;
int T, n, a[N], in[N];
void solve() {
  cin >> n;
  memset(in + 1, 0, sizeof(int) * n);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    in[a[i]]++;
  }
  vector<int> v;
  for (int i = 1; i <= n; ++i)
    if (!in[i])
      v.emplace_back(i);
  int ans = 2, front = 0, rear = v.size();
  while (front < rear) {
    ++ans;
    while (front < rear) {
      if (--in[a[v[front]]] == 0)
        v.emplace_back(a[v[front]]);
      ++front;
    }
    rear = v.size();
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}