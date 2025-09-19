/*
 * Problem URL : https://codeforces.com/contest/347/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long n(0);
  scanf("%ld", &n);
  long *perm = new long[n];
  for (int k = 0; k < n; k++) {
    scanf("%ld", perm + k);
  }

  long total(0);
  bool pair(0);
  for (int k = 0; k < n; k++) {
    if (perm[k] == k) {
      ++total;
    } else if (perm[perm[k]] == k) {
      pair = 1;
    }
  }

  if (pair) {
    total += 2;
  } else if (total < n) {
    ++total;
  }

  printf("%ld\n", total);
  return 0;
}
