/*
 * Problem URL : https://codeforces.com/problemset/problem/1936/A
 * Submit Date : 2025-08-20
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, k, l, mx, my, t;
char query(int a, int b, int c, int d) {
  printf("? %d %d %d %d\n", a, b, c, d);
  fflush(stdout);
  char anc;
  scanf(" %c", &anc);
  return anc;
}
void solve() {
  scanf("%d", &n);
  mx = my = 0;
  for (int i = 1; i < n; ++i)
    if (query(mx, mx, i, i) == '<')
      mx = i;
  char c;
  for (int i = 1; i < n; ++i) {
    c = query(mx, my, mx, i);
    if (c == '>')
      continue;
    if (c == '=' && query(my, my, i, i) == '<')
      continue;
    my = i;
  }
  printf("! %d %d\n", mx, my);
  fflush(stdout);
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}
