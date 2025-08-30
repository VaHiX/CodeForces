/*
 * Problem URL : https://codeforces.com/contest/1294/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, n;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &n);
    long mx = (a > b) ? a : b;
    mx = (mx > c) ? mx : c;
    long diff = (mx - a) + (mx - b) + (mx - c);
    bool possible = (n >= diff) && ((n - diff) % 3 == 0);
    puts(possible ? "YES" : "NO");
  }

  return 0;
}
