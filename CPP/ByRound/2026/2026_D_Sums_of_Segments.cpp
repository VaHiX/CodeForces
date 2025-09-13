/*
 * Problem URL : https://codeforces.com/contest/2026/problem/D
 * Submit Date : 2025-09-10
 */

#include <stdio.h>
using namespace std;
typedef long long ll;

int n, q, a[300003], s[300003];
ll c[300003], t[300003];
// s[i]: s(1,i)  c[i]: sum s(1,1)-s(1,i)  t[i]: sum s(1,1)-s(i,n)

ll calc(ll x) {
  int l = 0, r = n + 1;
  while (l + 1 < r) {
    int mid = (l + r) >> 1;
    if (1ll * (n + n - mid + 1) * mid / 2 <= x)
      l = mid;
    else
      r = mid;
  }
  x -= 1ll * (n + n - l + 1) * l / 2;
  ll sum = t[l] + c[x + l] - c[l] - x * s[l];
  return sum;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), s[i] = s[i - 1] + a[i], c[i] = c[i - 1] + s[i];
  for (int i = 1; i <= n; i++)
    t[i] = t[i - 1] + c[n] - c[i - 1] - 1ll * s[i - 1] * (n - i + 1);
  scanf("%d", &q);
  while (q--) {
    ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", calc(r) - calc(l - 1));
  }
}