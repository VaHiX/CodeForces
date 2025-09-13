/*
 * Problem URL : https://codeforces.com/problemset/problem/1817/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>
using namespace std;
const int o = 2e5 + 10;
int n, q, a[o], b[o];
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 2; i < n; ++i)
    b[i] = b[i - 1] + (a[i - 1] >= a[i] && a[i] >= a[i + 1]);
  for (int l, r; q--; printf("%d\n", r - l + 1 - (b[r - 1] - b[l]) * (l < r)))
    scanf("%d%d", &l, &r);
  return 0;
}