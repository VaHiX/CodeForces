/*
 * Problem URL : https://codeforces.com/problemset/problem/1858/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld\n", &a, &b, &c);
    puts((a + (c % 2) > b) ? "First" : "Second");
  }
}
