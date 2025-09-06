/*
 * Problem URL : https://codeforces.com/problemset/problem/2093/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long k;
    scanf("%ld", &k);
    puts(k % 2 ? "YES" : "NO");
  }
}
