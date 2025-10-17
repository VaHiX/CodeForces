/*
 * Problem URL : https://codeforces.com/problemset/problem/916/B
 * Submit Date : 2025-08-18
 */

#include <cstdio> /*By Citrus*/
const int karen = 2e5;
long long n;
int k, a[karen | 10], *b = a + (karen >> 2);
int main() {
  scanf("%lld%d", &n, &k);
  int cnt = 0;
  for (; n;)
    b[cnt] = n & 1, n >>= 1, k -= b[cnt++];
  if (k < 0)
    return puts("No"), 0;
  int q = cnt - 1;
  for (; b[q] <= k;)
    b[q - 1] += b[q] << 1, k -= b[q], b[q--] = 0;
  int p = 0;
  q < p ? p = q : 0;
  for (; p < cnt && !b[p]; ++p)
    ;
  for (; k; --p)
    if (b[p])
      b[p - 1] += 2, b[p]--, k--;
  puts("Yes");
  for (int i = cnt - 1; i >= p; --i)
    for (; b[i]--; printf("%d ", i))
      ;
}