/*
 * Problem URL : https://codeforces.com/contest/1725/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, tree[N];
long long s[N], v[N], Max, ans;
void update(int s) {
  for (; s <= m; s += s & -s)
    tree[s]++;
}
int getsum(int s) {
  int t = 0;
  for (; s; s -= s & -s)
    t += tree[s];
  return t;
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &s[i]), v[i] = s[i] += s[i - 1];
    if (s[i] < 0)
      return puts("-1"), 0;
    Max = max(Max, s[i]);
  }
  if (s[n] ^ Max)
    return puts("-1"), 0;
  sort(v + 1, v + n + 1), m = unique(v + 1, v + n + 1) - v - 1;
  for (int i = 1; i <= n; i++) {
    int p = m - (lower_bound(v + 1, v + m + 1, s[i]) - v);
    ans += getsum(p), update(p + 1);
  }
  cout << ans;
}