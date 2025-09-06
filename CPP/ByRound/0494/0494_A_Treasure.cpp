/*
 * Problem URL : https://codeforces.com/problemset/problem/494/A
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>
using namespace std;
char s[100005];
int n, k, cnt, m, t, tot;
int main() {
  scanf("%s", s);
  n = strlen(s);
  for (int i = 0; i < n; i++) {
    if (s[i] == '(')
      k++;
    if (s[i] == ')')
      k--;
    if (s[i] == '#')
      cnt++, k--, t = i;
    if (k < 0) {
      puts("-1");
      return 0;
    }
  }
  for (int i = t + 1; i <= n; i++) {
    if (s[i] == '(')
      tot++;
    if (s[i] == ')')
      tot--;
    tot = max(tot, 0);
  }
  if (tot > 0) {
    puts("-1");
    return 0;
  }
  for (int i = 1; i < cnt; i++)
    puts("1");
  printf("%d", k + 1);
  return 0;
}