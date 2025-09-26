/*
 * Problem URL : https://codeforces.com/problemset/problem/222/B
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <cstdio>

using namespace std;

int p[1001][1001], row[1001], col[1001];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  for (int r = 1; r <= n; ++r)
    row[r] = r;

  for (int c = 1; c <= m; ++c)
    col[c] = c;

  for (int r = 1; r <= n; ++r)
    for (int c = 1; c <= m; ++c)
      scanf("%d", &p[r][c]);

  while (k--) {
    char s[2];
    int x, y;
    scanf("%s%d%d", s, &x, &y);
    switch (s[0]) {
    case 'r':
      swap(row[x], row[y]);
      break;
    case 'c':
      swap(col[x], col[y]);
      break;
    case 'g':
      printf("%d\n", p[row[x]][col[y]]);
      break;
    default:
      break;
    }
  }
  return 0;
}
