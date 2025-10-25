/*
 * Problem URL : https://codeforces.com/problemset/problem/493/D
 * Submit Date : 2025-08-14
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld\n", &n);
  if (n % 2) {
    puts("black");
  } else {
    puts("white\n1 2");
  }

  return 0;
}
