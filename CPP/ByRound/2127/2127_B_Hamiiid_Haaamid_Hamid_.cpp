/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/B
 * Submit Date : 2025-08-14
 */

#include <cstdio>
#include <iostream>
using namespace std;
char a[200010];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", a + 1);
    int l = k, r = k, ans = 0x3f3f3f3f;
    while (a[l] == '.')
      l--;
    while (a[r] == '.')
      r++;
    printf("%d\n", max(min(k - 1, n - r + 1), min(n - (k + 1) + 1, l)) + 1);
  }
}