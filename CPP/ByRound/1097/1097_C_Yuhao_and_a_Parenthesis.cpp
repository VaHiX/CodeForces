/*
 * Problem URL : https://codeforces.com/contest/1097/problem/C
 * Submit Date : 2025-08-31
 */

#include <stdio.h>
int const N = 5e5 + 1;
int n, m, c, r, i, d[2 * N];
char s[N], *p;
int main() {
  scanf("%d", &n);
  while (n--) {
    m = c = 0;
    scanf("%s", s);
    for (p = s; *p; p++) {
      c += 81 - *p * 2;
      m = m < c ? m : c;
    }
    d[2 * (m < 0 ? -m : c) + (m < 0)] += m == (c < 0 ? c : 0);
  }
  for (; i < 2 * N; i += 2)
    r += d[i] < d[i + 1] ? d[i] : d[i + 1];
  printf("%d", r + d[0] / 2);
}