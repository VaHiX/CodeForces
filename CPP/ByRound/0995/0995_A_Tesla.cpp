/*
 * Problem URL : https://codeforces.com/contest/995/problem/A
 * Submit Date : 2025-09-02
 */

/*baad me nhi karna hai*/
#include <bits/stdc++.h>
using namespace std;
int n, k, a[5][51], tot;
struct node {
  int id, x, y;
  node(int a = 0, int b = 0, int c = 0) { id = a, x = b, y = c; }
} ans[20005];
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", &a[i][j]);
  int nx = 2, ny = 1, cnt = 0, sum = 0;
  while (cnt <= 20000 && sum != k) {
    int tx = nx, ty, gx, gy;
    nx == 2 ? ty = ny + 1 : ty = ny - 1;
    if (ty > n)
      tx++, ty--;
    if (ty < 1)
      tx--, ty++;
    gy = ty;
    tx == 2 ? gx = 1 : gx = 4;
    if (a[tx][ty] != 0) {
      if (a[tx][ty] == a[gx][gy])
        ans[++tot] = node(a[tx][ty], gx, gy), sum++, a[tx][ty] = 0;
      else if (!a[nx][ny])
        ans[++tot] = node(a[tx][ty], nx, ny), swap(a[tx][ty], a[nx][ny]);
    }
    nx = tx, ny = ty;
    cnt++;
  }
  if (sum == k) {
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
      printf("%d %d %d\n", ans[i].id, ans[i].x, ans[i].y);
  } else
    puts("-1");
  return 0;
}