/*
 * Problem URL : https://codeforces.com/problemset/problem/230/B
 * Submit Date : 2025-08-16
 */

#include <math.h>
#include <stdio.h>
int main() {
  int n;
  long long a, b, j;
  scanf("%i", &n);
  while (n--) {
    scanf("%I64d", &a);
    b = sqrt(a);
    for (j = 2; j * j <= b; j++)
      if (b % j == 0)
        break;
    puts((j * j > b && b * b == a && a > 1) ? "YES" : "NO");
  }
  return 0;
}