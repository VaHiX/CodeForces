/*
 * Problem URL : https://codeforces.com/contest/966/problem/A
 * Submit Date : 2025-09-04
 */

#include <iostream>
#define ll long long
const int inf = 0x3f3f3f3f;
using namespace std;
int n, m, v, c1, c2, q, a[120000], b[120000];
int main() {
  scanf("%d%d%d%d%d", &n, &m, &c1, &c2, &v);
  for (int i = 0; i < c1; i++)
    scanf("%d", &a[i]);
  for (int i = 0; i < c2; i++)
    scanf("%d", &b[i]);
  int q;
  scanf("%d", &q);
  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if (x1 == x2) {
      printf("%d\n", abs(y2 - y1));
      continue;
    }
    int temp = lower_bound(a, a + c1, y1) - a;
    int ans = inf;
    if (temp < c1) {
      ans = min(ans, abs(a[temp] - y1) + abs(a[temp] - y2) + abs(x1 - x2));
    }
    if (temp > 0) {
      ans = min(ans,
                abs(a[temp - 1] - y1) + abs(a[temp - 1] - y2) + abs(x1 - x2));
    }
    temp = lower_bound(b, b + c2, y1) - b;
    if (temp < c2) {
      ans = min(ans, abs(b[temp] - y1) + abs(b[temp] - y2) +
                         (abs(x1 - x2) + v - 1) / v);
    }
    if (temp > 0) {
      ans = min(ans, abs(b[temp - 1] - y1) + abs(b[temp - 1] - y2) +
                         (abs(x1 - x2) + v - 1) / v);
    }
    printf("%d\n", ans);
  }
  return 0;
}
