/*
 * Problem URL : https://codeforces.com/problemset/problem/1853/E
 * Submit Date : 2025-08-13
 */

#include <iostream>
#include <queue>
using namespace std;

#define ll long long

void solve() {
  int n, k, x, pre, i, j;
  ll ans;
  scanf("%d %d", &n, &k);
  priority_queue<int, vector<int>, greater<int>> q;
  ans = 0, pre = 0;
  for (i = 1; i <= n; i++) {
    scanf("%d", &x);
    x %= k;
    if (x > pre) {
      q.push(x - pre);
      ans += q.top();
      q.pop();
    } else {
      q.push(k + x - pre);
    }
    pre = x;
  }
  printf("%lld\n", ans);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}