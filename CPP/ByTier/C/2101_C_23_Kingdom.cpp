/*
 * Problem URL : https://codeforces.com/problemset/problem/2101/C
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;

int n, a[N], fa[N], pre[N], suf[N];

int findfa(int x) { return x == fa[x] ? x : fa[x] = findfa(fa[x]); }

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  for (int i = 1; i <= n; i++) {
    int x = findfa(a[i]);
    pre[i] = pre[i - 1];
    if (x) {
      pre[i]++;
      fa[x] = x - 1;
    }
  }
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  suf[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    int x = findfa(a[i]);
    suf[i] = suf[i + 1];
    if (x) {
      suf[i]++;
      fa[x] = x - 1;
    }
  }
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    ans += min(pre[i], suf[i + 1]);
  }
  cout << ans << "\n";
}

int main() {
  // freopen("in.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}