/*
 * Problem URL : https://codeforces.com/contest/930/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100100;
int dep[MAXN], num[MAXN];
int main() {
  int n, i, p, ans = 1;
  scanf("%d", &n);
  for (i = 2; i <= n; i++) {
    scanf("%d", &p);
    dep[i] = dep[p] + 1;
    num[dep[i]]++;
  }
  for (i = 0; i <= n; i++)
    ans += num[i] % 2;
  printf("%d", ans);
}
// 4973
