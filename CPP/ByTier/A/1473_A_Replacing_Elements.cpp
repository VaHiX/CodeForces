/*
 * Problem URL : https://codeforces.com/contest/1473/problem/A
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t, a[110];
  cin >> t;
  while (t--) {
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    sort(a, a + n);
    if (a[n - 1] > d && a[0] + a[1] > d)
      puts("NO");
    else
      puts("YES");
  }
  return 0;
}