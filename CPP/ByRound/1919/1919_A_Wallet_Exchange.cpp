/*
 * Problem URL : https://codeforces.com/problemset/problem/1919/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    a += b;
    puts(a % 2 ? "Alice" : "Bob");
  }
}
