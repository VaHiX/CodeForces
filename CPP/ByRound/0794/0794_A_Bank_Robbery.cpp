// Problem: CF 794 A - Bank Robbery
// https://codeforces.com/contest/794/problem/A

/*
 * Problem: Bank Robbery
 * 
 * Purpose: Determine the maximum number of banknotes Oleg can collect
 *          from safes, avoiding the guards at positions b and c.
 * 
 * Algorithm:
 *   - Iterate through each banknote's position.
 *   - Check if the banknote is between the two guards (b < x < c).
 *   - Count such valid banknotes.
 * 
 * Time Complexity: O(n), where n is the number of banknotes.
 * Space Complexity: O(1), only using a few variables for computation.
 */

#include <cstdio>
int main() {
  long a, b, c;  // Positions of Oleg, first guard, and second guard
  scanf("%ld %ld %ld", &a, &b, &c);
  long n;  // Number of banknotes
  scanf("%ld", &n);
  long count(0);  // Counter for valid banknotes
  while (n--) {
    long x;  // Position of current banknote
    scanf("%ld", &x);
    // Check if banknote is not guarded and within reachable range
    count += ((b < x) && (x < c));
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/