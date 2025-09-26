/*
 * Problem URL : https://codeforces.com/problemset/problem/2075/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    printf("%ld\n", (n + k - 3) / (k - 1));
  }
}
