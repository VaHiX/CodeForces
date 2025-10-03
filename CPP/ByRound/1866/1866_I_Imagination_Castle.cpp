/*
 * Problem URL : https://codeforces.com/contest/1866/problem/I
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, k, px, py, x[200005], y[200005], xx[200005], yy[200005];

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%d %d", &x[i], &y[i]);
    xx[x[i]] = max(xx[x[i]], y[i]);
    yy[y[i]] = max(yy[y[i]], x[i]);
  }
  if (n == 1 && m == 1) {
    puts("Bhinneka");
    return 0;
  }
  px = n;
  py = m;
  while (px > 1 && py > 1) {
    --px;
    --py;
    while (1) {
      if (px >= 1 && xx[px] > py) {
        --px;
        continue;
      }
      if (py >= 1 && yy[py] > px) {
        --py;
        continue;
      }
      break;
    }
    if (px == 1 && py == 1) {
      puts("Bhinneka");
      return 0;
    }
  }
  puts("Chaneka");
  return 0;
}
