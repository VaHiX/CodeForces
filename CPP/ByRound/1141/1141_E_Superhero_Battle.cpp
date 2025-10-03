/*
 * Problem URL : https://codeforces.com/contest/1141/problem/E
 * Submit Date : 2025-08-29
 */

#include <cstdio>
typedef long long LL;
const int N = 2e5 + 50;
LL H, Ans, x, y;
int n, a[N];
int main() {
  scanf("%I64d%d", &H, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    x += a[i];
    if (y > x)
      y = x;
    if (H + x <= 0) {
      printf("%d\n", i);
      return 0;
    }
  }
  if (x >= 0) {
    puts("-1");
    return 0;
  }
  x = -x;
  Ans = 1ll * n * ((H + y) / x + ((H + y) % x > 0));
  H = H - 1ll * ((H + y) / x + ((H + y) % x > 0)) * x;
  for (int i = 1; i <= n; i++) {
    H += a[i];
    if (H <= 0) {
      printf("%I64d\n", Ans + i);
      return 0;
    }
  }
}