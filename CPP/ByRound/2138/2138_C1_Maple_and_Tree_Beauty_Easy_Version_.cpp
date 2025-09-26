/*
 * Problem URL : https://codeforces.com/contest/2138/problem/C1
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
void init();
void Solve();
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  init();
  cin >> T;
  while (T--)
    Solve();
  return 0;
}
void init() {}
int n, k, dep[200005], cnt[200005], sum[200005], D, res;
bitset<200005> dp;
vector<int> q, p;
void Solve() {
  cin >> n >> k;
  dp.reset();
  for (int i = 1; i <= n; i++)
    sum[i] = cnt[i] = 0;
  dep[1] = 1;
  cnt[1] = 1;
  for (int i = 2, f; i <= n; i++) {
    cin >> f;
    dep[i] = dep[f] + 1;
    cnt[dep[i]]++;
    sum[f]++;
  }
  D = n;
  for (int i = 1; i <= n; i++)
    if (!sum[i])
      D = min(D, dep[i]);
  q.clear();
  p.clear();
  for (int i = 1; i <= D; i++)
    q.push_back(cnt[i]);
  sort(q.begin(), q.end());
  for (int i = 0; i < q.size(); i++) {
    int j = i;
    while (j < q.size() && q[j] == q[i])
      j++;
    j--;
    int t = j - i + 1;
    for (int z = 1; z <= t; z <<= 1) {
      p.push_back(z * q[i]);
      t -= z;
    }
    if (t)
      p.push_back(t * q[i]);
    i = j;
  }
  dp[0] = 1;
  res = 0;
  for (auto x : p) {
    res += x;
    dp |= (dp << x);
  }
  if (res <= k || res <= n - k) {
    cout << D << endl;
    return;
  }
  for (int i = 0; i <= res; i++)
    if (dp[i] && i <= k && res - i <= n - k) {
      cout << D << endl;
      return;
    }
  cout << D - 1 << endl;
  return;
}
