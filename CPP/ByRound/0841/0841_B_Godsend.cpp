/*
 * Problem URL : https://codeforces.com/problemset/problem/841/B
 * Submit Date : 2025-08-16
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  while (n--) {
    long a;
    scanf("%ld", &a);
    if (a & 1) {
      puts("First");
      return 0;
    }
  }

  puts("Second");
  return 0;
}
