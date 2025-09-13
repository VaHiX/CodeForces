/*
 * Problem URL : https://codeforces.com/problemset/problem/991/D
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
char s[105], t[105];
int n, a, b, i, w;
int main() {
  for (scanf("%s%s", s, t), n = strlen(s); i < n; i++)
    b = (s[i] == 48) + (t[i] == 48), w += (a + b) / 3,
    a = (a + b > 2 ? a + b - 3 : b);
  return printf("%d", w), 0;
}