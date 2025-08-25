/*
 * Problem URL : https://codeforces.com/problemset/problem/1747/C
 * Submit Date : 2025-08-21
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a;
    scanf("%ld", &a);
    bool res(false);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < a) {
        res = true;
      }
    }

    puts(res ? "Alice" : "Bob");
  }
}
