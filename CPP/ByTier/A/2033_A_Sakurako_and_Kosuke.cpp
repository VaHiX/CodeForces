/*
 * Problem URL : https://codeforces.com/problemset/problem/2033/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    n = (n > 0 ? n : -n);
    puts(n % 2 ? "Kosuke" : "Sakurako");
  }
}
