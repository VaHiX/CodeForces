/*
 * Problem URL : https://codeforces.com/contest/256/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int n, a[10100], v[1001000];
int p[10100], nx[10100], ans = 1, pr;

int solve(int x, int y, int z) {
  int t = x;
  while (t <= y)
    t = nx[t];
  if (t <= n)
    return solve(y, t, z + 1);
  return z;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) {
    p[i] = v[a[i]];
    v[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    nx[i] = n + 1, pr = i;
    for (int j = i + 1; j <= n; j++)
      if (a[j] == a[i]) {
        nx[pr] = j;
        pr = j;
        break;
      }
  }
  for (int i = 1; i <= n; i++)
    if (!p[i]) {
      for (int j = i + 1; j <= n; j++) {
        if (p[j] >= i)
          continue;
        ans = max(ans, solve(i, j, 2));
      }
      int cur = 1;
      for (int j = i + 1; j <= n; j++)
        if (a[i] == a[j])
          cur++;
      ans = max(ans, cur);
    }
  cout << ans << endl;
}
