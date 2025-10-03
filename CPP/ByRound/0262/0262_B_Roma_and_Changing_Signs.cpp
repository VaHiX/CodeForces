/*
 * Problem URL : https://codeforces.com/problemset/problem/262/B
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>

int main() {

  long n(0), k(0);
  scanf("%ld %ld", &n, &k);
  long total(0);
  long currentNumber(0), minNumber(100000);

  for (int p = 0; p < n; p++) {
    scanf("%ld", &currentNumber);
    if (currentNumber < 0 && k > 0) {
      currentNumber *= -1;
      --k;
    }
    total += currentNumber;
    if (currentNumber < minNumber) {
      minNumber = currentNumber;
    }
  }
  if (k % 2) {
    total -= 2 * minNumber;
  }

  printf("%ld\n", total);
  return 0;
}
