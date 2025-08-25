/*
 * Problem URL : https://codeforces.com/problemset/problem/1713/C
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005], m, p;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    m = n;
    a[0] = 0;
    while (n > 1) {
      p = sqrt(n);
      if (p * p < n - 1)
        p++;
      for (int i = n - 1; p * p - i < n; i--)
        a[i] = p * p - i;
      n = p * p - n + 1;
    }
    for (int i = 0; i < m; i++)
      printf("%d ", a[i]);
    printf("\n");
  }
}
