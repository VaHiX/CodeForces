// Problem: CF 1826 C - Dreaming of Freedom
// https://codeforces.com/contest/1826/problem/C

/*
 * C. Dreaming of Freedom
 *
 * Purpose: Determine whether a voting process among n programmers and m algorithm choices
 *          can continue indefinitely or will always end in a single choice.
 *
 * Algorithm:
 * - If n == 1: Only one programmer, so they will always choose one option → "YES"
 * - If m >= n: There are more options than programmers, so at least one option
 *   will not be chosen by any programmer; if tie occurs in voting, multiple choices remain.
 *   This leads to a possibility of infinite loop → "NO"
 * - Otherwise (n > 1 and n < m):
 *   We check if n is prime, and if it's divisible by any number p up to sqrt(n).
 *   If it is, then there exists a way to split votes such that a tie occurs.
 *   This results in indefinite continuation → "NO".
 *   Otherwise, we will eventually converge to one option → "YES"
 *
 * Time Complexity: O(sqrt(n)) per test case due to prime check loop
 * Space Complexity: O(1) - only using a constant amount of variables
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    if (n == 1) {
      puts("YES"); // Only one person → always picks one option
    } else if (m >= n) {
      puts("NO"); // More choices than people → can create ties leading to infinite loop
    } else {
      bool out(false);
      for (long p = 2; !out && p <= m && p * p <= n; p++) {
        out |= (n % p == 0); // Check if n is divisible by p
      }
      puts(out ? "NO" : "YES"); // If divisible, a tie is possible → NO. Else YES.
    }
  }
}


// https://github.com/VaHiX/codeForces/