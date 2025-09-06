/*
 * Problem URL : https://codeforces.com/contest/584/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/584/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  int n, t;
  scanf("%d %d\n", &n, &t);

  if (t == 10) {
    if (n == 1) {
      puts("-1");
    } else {
      printf("1");
      for (int p = 0; p < n - 1; p++) {
        printf("0");
      }
    }
  } else {
    for (int p = 0; p < n; p++) {
      printf("%d", t);
    }
  }

  return 0;
}
