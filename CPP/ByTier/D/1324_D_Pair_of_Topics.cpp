/*
 * Problem URL : https://codeforces.com/contest/1324/problem/D
 * Submit Date : 2025-09-08
 */

#import <regex>
int i, j, n, a[7 << 15];
long long r;
int main() {
  for (scanf("%d", &n); i < n; i++)
    scanf("%d", a + i);
  for (; j < n; j++)
    scanf("%d", &i), a[j] -= i;
  std::sort(a, a + n);
  while (--j)
    if (a[n - j - 1] + a[n - 1] > 0)
      r += j, n--;
  printf("%lld", r);
}