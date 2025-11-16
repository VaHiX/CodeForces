// Problem: CF 841 B - Godsend
// https://codeforces.com/contest/841/problem/B

/*
 * Problem: B. Godsend
 * Purpose: Determine the winner of a game where two players remove subsegments from an array based on the sum's parity.
 *          The first player removes subsegments with odd sums, the second with even sums.
 *          The player who cannot make a move loses.
 *
 * Algorithm:
 *   - If there exists at least one odd number in the array, the first player can always win by removing
 *     that single odd number (which forms a subsegment of odd sum). This is because the first player
 *     can always ensure a move exists as long as there's an odd number.
 *   - If all numbers are even, the first player cannot make a move (no odd subsegment exists),
 *     so the second player wins by default.
 *
 * Time Complexity: O(n) - We scan the array once.
 * Space Complexity: O(1) - Only using constant extra space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  while (n--) {
    long a;
    scanf("%ld", &a);
    if (a & 1) {  // Check if the current number is odd
      puts("First");  // First player can win by taking this odd number
      return 0;
    }
  }
  puts("Second");  // No odd number found, second player wins
  return 0;
}


// https://github.com/VaHiX/CodeForces/