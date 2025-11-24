// Problem: CF 468 A - 24 Game
// https://codeforces.com/contest/468/problem/A

/*
 * Problem: 24 Game
 * Purpose: Determine if it's possible to combine numbers 1 through n using
 *          operations +, -, * to get 24. If possible, output a sequence of operations.
 *
 * Algorithm:
 * - For n < 4: Impossible to form 24 (too few numbers)
 * - For even n: Use pattern involving 1*2=2, 2*3=6, 6*4=24, then use remaining numbers to
 *               construct 1s to multiply with 24.
 * - For odd n: Use pattern involving 1+5=6, 4*6=24, 3-2=1, then use remaining number pairs
 *               to construct 1s to multiply with 24.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  if (n < 4) {
    puts("NO");
  } else if (n % 2 == 0) {
    puts("YES");
    puts("1 * 2 = 2");
    puts("2 * 3 = 6");
    puts("6 * 4 = 24");
    for (long p = 6; p <= n; p += 2) {
      printf("%ld - %ld = 1\n", p, p - 1);
      puts("24 * 1 = 24");
    }
  } else if (n % 2 == 1) {
    puts("YES");
    puts("1 + 5 = 6");
    puts("4 * 6 = 24");
    puts("3 - 2 = 1");
    puts("1 * 24 = 24");
    for (long p = 7; p <= n; p += 2) {
      printf("%ld - %ld = 1\n", p, p - 1);
      puts("24 * 1 = 24");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/