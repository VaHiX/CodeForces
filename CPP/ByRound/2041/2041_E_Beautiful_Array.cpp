/*
 * Problem URL : https://codeforces.com/problemset/problem/2041/E
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long a, b;
  scanf("%ld %ld", &a, &b);
  printf("3\n-600 %ld %ld\n", b, 3 * a - b + 600);
}
