/*
 * Problem URL : https://codeforces.com/contest/365/problem/B
 * Submit Date : 2025-09-08
 */

#include <cstdio>

int main() {

  long n(0);
  scanf("%ld", &n);
  long best(0), previousB(0), previousA(0), current(0), total(0);

  for (int k = 0; k < n; k++) {

    previousB = previousA;
    previousA = current;
    scanf("%ld", &current);

    if (current == previousA + previousB || total <= 1) {
      ++total;
      if (total > best) {
        best = total;
      }
    } else {
      total = 2;
    }
  }

  printf("%ld\n", best);

  return 0;
}
