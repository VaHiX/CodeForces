/*
 * Problem URL : https://codeforces.com/problemset/problem/2123/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(n % 4 ? "Alice" : "Bob");
  }
}
