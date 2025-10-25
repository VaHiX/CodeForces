// Problem: CF 1735 B - Tea with Tangerines
// https://codeforces.com/contest/1735/problem/B

/* 
 * Problem: B. Tea with Tangerines
 * Purpose: Given n pieces of tangerine peel with sizes a_i, determine the minimum number of steps 
 *          to ensure that for every pair of pieces, their sizes differ strictly less than twice.
 *          Each step allows dividing a piece of size x into two positive integer sized pieces y and z such that y + z = x.
 *          
 * Algorithm:
 *   - Sort input array (implicitly handled by input order).
 *   - For each piece, calculate how many divisions are needed so that the resulting smallest piece
 *     is at least half of the current piece size.
 *   - Use greedy approach: always split pieces to maintain condition.
 * 
 * Time Complexity: O(n log n) due to sorting (if not pre-sorted) or O(n) if already sorted.
 * Space Complexity: O(1) - only a few variables used.
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    long y = 2 * x - 1; // Threshold for piece size comparison
    long long res(0);   // Result counter for total steps
    
    // Process all pieces except the first one (already considered in x)
    for (long p = 1; p < n; p++) {
      long a;
      scanf("%ld", &a);
      // Calculate number of splits needed to make largest piece <= 2 * x - 1
      res += ((a + y - 1) / y) - 1;
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/