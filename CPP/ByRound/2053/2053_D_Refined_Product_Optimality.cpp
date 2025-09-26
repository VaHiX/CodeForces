/*
 * Problem URL : https://codeforces.com/problemset/problem/2053/D
 * Submit Date : 2025-08-24
 */

#include <algorithm>
#include <stdio.h>
using namespace std;
const int p = 998244353;
typedef long long ll;

int a[200002], b[200002], c[200002], d[200002];

ll ksm(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1)
      ans = ans * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ans;
}

void solve(int n, int q) {
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), c[i] = a[i];
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]), d[i] = b[i];
  sort(c + 1, c + n + 1);
  sort(d + 1, d + n + 1);
  ll ans = 1;
  for (int i = 1; i <= n; i++)
    ans = ans * min(c[i], d[i]) % p;
  printf("%lld ", ans);
  while (q--) {
    int o, x;
    scanf("%d%d", &o, &x);
    if (o == 1) {
      int i = upper_bound(c + 1, c + n + 1, a[x]) - c - 1;
      if (c[i] < d[i])
        ans = ans * ksm(c[i], p - 2) % p * (c[i] + 1) % p;
      c[i]++;
      a[x]++;
    } else {
      int i = upper_bound(d + 1, d + n + 1, b[x]) - d - 1;
      if (d[i] < c[i])
        ans = ans * ksm(d[i], p - 2) % p * (d[i] + 1) % p;
      d[i]++;
      b[x]++;
    }
    printf("%lld ", ans);
  }
}

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    int n, q;
    scanf("%d%d", &n, &q);
    solve(n, q);
    putchar('\n');
  }
}