/*
 * Problem URL : https://codeforces.com/problemset/problem/670/E
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 500007;
int n, m, p, t;
char s[N], op[N];
int l[N + 1], r[N + 1];
int match[N], stk[N], top = 0;
int main() {
  scanf("%d%d%d", &n, &m, &p);
  scanf("%s", s + 1);
  r[0] = 1;
  for (int i = 1; i <= n; i++) {
    l[i] = i - 1;
    if (i == n)
      r[i] = N;
    else
      r[i] = i + 1;
  }
  l[N] = n;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(')
      stk[++top] = i;
    else {
      match[i] = stk[top];
      match[stk[top]] = i;
      --top;
    }
  }
  scanf("%s", op);
  for (int i = 0; i < m; i++) {
    if (op[i] == 'L')
      p = l[p];
    else if (op[i] == 'R')
      p = r[p];
    else {
      int q = match[p];
      if (p > q)
        swap(p, q);
      r[l[p]] = r[q];
      l[r[q]] = l[p];
      if (r[q] != N)
        p = r[q];
      else
        p = l[p];
    }
  }
  for (int i = r[0]; i != N; i = r[i]) {
    putchar(s[i]);
  }
  return 0;
} // 16963077717733939985