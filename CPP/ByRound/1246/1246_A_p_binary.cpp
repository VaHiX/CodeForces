// Problem: CF 1246 A - p-binary
// https://codeforces.com/contest/1246/problem/A

/*
 * Problem: Find minimum number of p-binary numbers (2^x + p) to sum to n.
 * Algorithm: Brute-force search over possible counts of terms.
 * Time Complexity: O(log n * log n) - loop up to log n, and each iteration does popcount which is O(log n)
 * Space Complexity: O(1) - only using constant extra space
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int n, m; // n is input number, m represents p (shift value)

int solve() {
  for (int i = 1; i <= 10000; ++i) { // Try up to 10000 terms
    n -= m; // Subtract p from n, simulating one term of (2^x + p)
    if (__builtin_popcount(n) <= i && i <= n) // Check if number of set bits in n is <= i and i <= n
      return i;
  }
  return -1; // Not possible to represent
}

int main() {
  scanf("%d %d", &n, &m);
  printf("%d\n", solve());
}


// https://github.com/VaHiX/codeForces/