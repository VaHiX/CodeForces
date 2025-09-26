/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/G
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 100000;
int s[N], a[N], u[N], v[N], w[N];
int ask(int u, int v) {
  int x;
  printf("? %d %d\n", u, v);
  fflush(stdout);
  scanf("%d", &x);
  return x;
}
int main() {
  int T, n, k, b, m, i, x;
  for (scanf("%d", &T); T; T--) {
    scanf("%d", &n);
    k = (n + 1) / 3;
    printf("%d\n", k);
    fflush(stdout);
    b = m = 0;
    for (i = 1; i <= n; i++)
      if (!b)
        s[b++] = i;
      else if (b == 1) {
        x = ask(s[0], i);
        s[b++] = i;
      } else if (ask(s[b - 1], i) == x)
        s[b++] = i;
      else {
        a[m] = x;
        u[m] = s[b - 2];
        v[m] = s[b - 1];
        w[m++] = i;
        b -= 2;
      }
    printf("!");
    for (i = 0; i < b - 1; i += 2) {
      if (!k)
        break;
      k--;
      printf(" %d %d", s[i], s[i ^ 1]);
    }
    for (i = 0; i < m; i++) {
      if (!k)
        break;
      k--;
      if (a[i] == x)
        printf(" %d %d", u[i], v[i]);
      else
        printf(" %d %d", v[i], w[i]);
    }
    printf("\n");
    fflush(stdout);
  }
  return 0;
}