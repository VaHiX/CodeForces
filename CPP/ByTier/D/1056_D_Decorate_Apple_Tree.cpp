/*
 * Problem URL : https://codeforces.com/contest/1056/problem/D
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
#define mn 1111111
using namespace std;
int n, i = 2, a[mn], z[mn];
int main() {
  for (scanf("%d", &n); i <= n; i++)
    scanf("%d", a + i);
  for (i = n; i; i--) {
    if (!z[i])
      z[i]++;
    z[a[i]] += z[i];
  }
  sort(z + 1, z + 1 + n);
  for (i = 1; i <= n; i++)
    printf("%d ", z[i]);
}