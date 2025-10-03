/*
 * Problem URL : https://codeforces.com/problemset/problem/1839/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    printf("%ld\n", ((n + k - 1) / k) + ((k > 1) && (n % k != 1)));
  }
}
