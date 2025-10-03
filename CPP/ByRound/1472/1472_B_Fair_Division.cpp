/*
 * Problem URL : https://codeforces.com/contest/1472/problem/B
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ones(0), twos(0);
    while (n--) {
      long x;
      scanf("%ld", &x);
      ones += (x == 1);
      twos += (x == 2);
    }
    bool possible(true);
    if (ones % 2) {
      possible = false;
    } else if ((ones == 0) && (twos % 2)) {
      possible = false;
    }
    puts(possible ? "YES" : "NO");
  }
}
