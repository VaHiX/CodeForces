/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>
#include <vector>

int main() {

  long n(0);
  scanf("%ld", &n);
  long currentDiv(2), total(1);

  while (n > 1) {
    if (currentDiv * currentDiv > n) {
      total += n;
      break;
    } else if (n % currentDiv == 0) {
      total += n;
      n /= currentDiv;
    } else {
      ++currentDiv;
    }
  }

  printf("%ld\n", total);

  return 0;
}
