/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>

int main() {

  long x, y;
  scanf("%ld %ld\n", &x, &y);
  double actual = x * x + y * y;
  long total = sqrt(actual);
  if (total * total == actual) {
    puts("black");
  } else {
    if (x * y < 0) {
      ++total;
    }
    puts(total % 2 ? "white" : "black");
  }

  return 0;
}
