/*
 * Problem URL : https://codeforces.com/contest/2039/problem/H1
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 555;
int n, a[N];
int main() {
  int T, i, j, x, y;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", a + i);
    if (n == 2) {
      if (a[0] > a[1])
        printf("1\nDR\n");
      else
        printf("0\n");
      continue;
    }
    printf("%d\n", n * 2);
    for (i = 0; i < n * 2; i++) {
      for (j = 2; j < n; j += 2) {
        x = (i + j - 1) % n;
        y = (i + j) % n;
        if ((a[x] < a[y]) ^ (x < y))
          printf("DDRR"), swap(a[x], a[y]);
        else
          printf("DRDR");
      }
      if (n % 2 == 0)
        printf("DR");
      printf("\n");
    }
  }
  return 0;
}