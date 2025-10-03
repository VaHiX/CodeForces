/*
 * Problem URL : https://codeforces.com/contest/575/problem/D
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/575/problem/D
 * Submit Date : 2025-09-02
 */

#include <cstdio>

int main() {

  const int n = 1000;
  printf("%d\n", 2 * n);
  for (int p = 1; p <= n; p++) {
    printf("%d 1 %d 2\n", p, p);
  }
  for (int p = n; p >= 1; p--) {
    printf("%d 1 %d 2\n", p, p);
  }

  return 0;
}
