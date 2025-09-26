/*
 * Problem URL : https://codeforces.com/problemset/problem/2014/B
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long odd = ((k + (n % 2)) / 2) % 2;
    puts(odd ? "NO" : "YES");
  }
}
