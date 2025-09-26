/*
 * Problem URL : https://codeforces.com/contest/2031/problem/C
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int T, n;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int x(1);
    if (n & 1) {
      if (n <= 25) {
        puts("-1");
        continue;
      }
      printf("1 2 2 3 3 4 4 5 5 1 6 6 7 7 8 8 9 9 10 10 11 11 13 12 12 1 13 "),
          x = 14, n -= 27;
    }
    n >>= 1;
    for (int i(0); i < n; ++i)
      printf("%d %d ", x + i, x + i);
    puts("");
  }
  return 0;
}