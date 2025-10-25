/*
 * Problem URL : https://codeforces.com/contest/2039/problem/C2
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int t;
int x;
LL m;
void solve() {
  scanf("%d%lld", &x, &m);
  LL ans = m / x - 1, a = m / x * x, b = a + x;
  ans += ((x ^ a) <= m) + ((x ^ b) <= m);
  for (int i = 1; i <= min(x - 1LL, m); i++)
    ans += (x ^ i) % i == 0;
  printf("%lld\n", ans);
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}
