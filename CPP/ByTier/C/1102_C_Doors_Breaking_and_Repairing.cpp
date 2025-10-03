/*
 * Problem URL : https://codeforces.com/problemset/problem/1102/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100

#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)

#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)

#define pb push_back
#define pp pair<int, int>

using namespace std;

int main() {

  int i, j, k;
  int n, m;
  int x, y, cnt = 0;

  sf(n);
  sff(x, y);

  int a[n];
  for (i = 0; i < n; i++)
    sf(a[i]);

  if (x > y) {
    pf(n);
    return 0;
  }

  k = 0;
  for (i = 0; i < n; i++) {
    if (a[i] <= x)
      k++;
  }

  if (k % 2 == 0)
    pf(k / 2);
  else
    pf(k / 2 + 1);

  return 0;
}
