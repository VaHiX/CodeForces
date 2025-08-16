/*
 * Problem URL : https://codeforces.com/problemset/problem/2040/B
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(1), last(1);
    while (last < n) {
      ++cnt;
      last = 2 * last + 2;
    }

    printf("%ld\n", cnt);
  }
}
