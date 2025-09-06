/*
 * Problem URL : https://codeforces.com/problemset/problem/2085/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int t, n, k;
priority_queue<int> q;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  for (int iiii = 1; iiii <= t; iiii++) {
    cin >> n >> k;
    long long ans = 0;
    while (q.size()) {
      q.pop();
    }
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      q.push(x);
      if ((n - i + 1) % (k + 1) == 0 && n - i) {
        ans += q.top();
        q.pop();
      }
    }
    cout << ans << "\n";
  }
  return 0;
}