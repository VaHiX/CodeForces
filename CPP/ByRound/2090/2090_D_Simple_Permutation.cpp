/*
 * Problem URL : https://codeforces.com/problemset/problem/2090/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, n;
int isp(ll x) {
  if (x == 1)
    return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}
int main() {
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    scanf("%d", &n);
    if (n == 2)
      printf("2 1\n");
    else if (n == 3)
      printf("2 1 3\n");
    else {
      for (int i = n / 2; i > 0; i--) {
        if (isp(i)) {
          printf("%d ", i);
          for (int j = i - 1; j > 0; j--)
            printf("%d %d ", j, i - j + i);
          for (int j = i + i; j <= n; j++)
            printf("%d ", j);
          printf("\n");
          break;
        }
      }
    }
  }
  return 0;
}