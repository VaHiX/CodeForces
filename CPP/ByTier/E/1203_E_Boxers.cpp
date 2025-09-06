/*
 * Problem URL : https://codeforces.com/problemset/problem/1203/E
 * Submit Date : 2025-08-19
 */

#include <cstdio>
int n, a[150010], tong[150010], ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), tong[a[i]]++;
  for (int i = 1; i <= 150001; i++)
    tong[i - 1] ? ans++
                : (tong[i]   ? ans++,
                   tong[i]-- : (tong[i + 1] ? ans++, tong[i + 1]-- : 1));
  printf("%d\n", ans);
}