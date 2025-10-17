/*
 * Problem URL : https://codeforces.com/contest/610/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/610/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld\n", &n);
  if (n % 2) {
    puts("0");
  } else {
    printf("%ld\n", (n - 1) / 4);
  }

  return 0;
}
