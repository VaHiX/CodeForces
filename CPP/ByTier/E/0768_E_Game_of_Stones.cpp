// Problem: CF 768 E - Game of Stones
// https://codeforces.com/contest/768/problem/E

/*
 * Purpose: Determine if Jon can win the modified Game of Stones.
 * 
 * Algorithm: This problem is a variant of the Nim game, where each pile's
 *            effective size is reduced to the largest triangular number that
 *            fits into it. The key insight is that for each pile, we compute
 *            a "grundy number" (or mex) derived from the triangular number
 *            decomposition. These are then XORed together to determine the
 *            overall game state.
 *
 * Time Complexity: O(n * sqrt(s_i)) where n is the number of piles and s_i
 *                  is the number of stones in each pile. In practice, since
 *                  s_i <= 60, this is effectively O(n).
 *
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long f(0);  // Initialize XOR accumulator for game state
  while (n--) {
    long x;
    scanf("%ld", &x);
    long a(1), k(1);  // 'a' is the triangle number index, 'k' tracks the last valid subtraction
    while (x >= a) {  // Loop to find the largest triangular number <= x
      x -= a;
      k = a;  // Store the largest triangular number used
      ++a;    // Increment to next triangular number
    }
    f ^= k;  // XOR the result with the grundy number for this pile
  }
  puts(f ? "NO" : "YES");  // If f is non-zero, Sam (first player) wins, so Jon loses -> NO
  return 0;
}


// https://github.com/VaHiX/CodeForces/