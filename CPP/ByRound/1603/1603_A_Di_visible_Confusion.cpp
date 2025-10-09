/*
 * Problem URL : https://codeforces.com/contest/1603/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>

using namespace std;
int t, n, a[100001], flag;

signed main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    flag = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      int k = 0;
      while (a[i] % (i + 1 - k) == 0 && k <= i - 1)
        k++;
      if (k == i)
        flag = 1;
    }
    if (flag)
      puts("NO");
    else
      puts("YES");
  }
  return 0;
}