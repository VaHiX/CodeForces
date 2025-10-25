/*
 * Problem URL : https://codeforces.com/contest/925/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
const int inf = INT_MAX;
int n, m, cl, ce, v, q, L[100005], E[100005];
int wk(int sx, int sy, int ex, int ey) {
  if (sx == ex)
    return abs(sy - ey);
  int k = lower_bound(L, L + cl, sy) - L, ans = inf;
  if (k < cl) {
    int T = L[k];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex), ans);
  }
  if (k > 0) {
    int T = L[k - 1];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex), ans);
  }
  k = lower_bound(E, E + ce, sy) - E;
  if (k < ce) {
    int T = E[k];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex) / v +
                  (((abs(sx - ex) % v) == 0) ? 0 : 1),
              ans);
  }
  if (k > 0) {
    int T = E[k - 1];
    ans = min(abs(sy - T) + abs(ey - T) + abs(sx - ex) / v +
                  (((abs(sx - ex) % v) == 0) ? 0 : 1),
              ans);
  }
  return ans;
}
int main() {
  scanf("%d%d%d%d%d", &n, &m, &cl, &ce, &v);
  for (int i = 0; i < cl; i++)
    scanf("%d", &L[i]);
  for (int i = 0; i < ce; i++)
    scanf("%d", &E[i]);
  sort(L, L + cl);
  sort(E, E + ce);
  scanf("%d", &q);
  while (q--) {
    int sx, sy, ex, ey;
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    printf("%d\n", wk(sx, sy, ex, ey));
  }
}
