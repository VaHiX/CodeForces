/*
 * Problem URL : https://codeforces.com/problemset/problem/2071/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long k;
    scanf("%ld", &k);
    puts((k - 1) % 3 ? "NO" : "YES");
  }
}
