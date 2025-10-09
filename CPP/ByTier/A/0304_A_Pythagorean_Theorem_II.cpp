/*
 * Problem URL : https://codeforces.com/contest/304/problem/A
 * Submit Date : 2025-09-06
 */

#include <cmath>
#include <cstdio>

int main() {

  long n(0);
  scanf("%ld", &n);
  const long maxSquare = n * n;

  int total(0);
  for (long a = 1; a < n; a++) {
    for (long b = a; b < n; b++) {
      long sumOfSquares = a * a + b * b;
      if (sumOfSquares > maxSquare) {
        break;
      }
      int temp = sqrt(sumOfSquares);
      if (temp * temp == sumOfSquares) {
        ++total;
      }
    }
  }

  printf("%d\n", total);
  return 0;
}
