/*
 * Problem URL : https://codeforces.com/problemset/problem/689/A
 * Submit Date : 2025-08-14
 */

#include <cstdio>

const int op[10] = {8, 6, 7, 3, 14, 15, 11, 12, 15, 9};

int n, ans;
char s[555];

int main() {
  scanf("%d%s", &n, s);
  ans = 15;
  for (int i = 0; i < n; i++)
    ans &= op[s[i] - '0'];
  printf("%s\n", ans ? "NO" : "YES");
  return 0;
}