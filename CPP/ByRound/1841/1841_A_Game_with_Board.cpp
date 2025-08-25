/*
 * Problem URL : https://codeforces.com/problemset/problem/1841/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(n < 5 ? "Bob" : "Alice");
  }
}
