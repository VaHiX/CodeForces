/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  long *value = new long[n];
  for (int k = 0; k < n; k++) {
    scanf("%ld", value + k);
  }

  long output = 0, currentMax = -30000000;
  for (int div = 1; div <= n / 3; div++) {
    if (n % div != 0) {
      continue;
    }
    for (int rem = 0; rem < div; rem++) {
      output = 0;
      for (int k = 0; k < n / div; k++) {
        output += value[div * k + rem];
      }
      if (output > currentMax) {
        currentMax = output;
      }
    }
  }

  printf("%ld\n", currentMax);
  return 0;
}
