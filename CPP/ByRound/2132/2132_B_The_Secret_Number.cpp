/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/B
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int m, k, l, r, t, anc;
long long n, ans[10010];
void solve() {
  anc = 0;
  scanf("%lld", &n);
  for (long long i = 10; i < n; i *= 10)
    if (!(n % (i + 1)))
      ans[anc++] = n / (i + 1);
  printf("%d\n", anc);
  while (anc--)
    printf("%lld%c", ans[anc], " \n"[!anc]);
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}
