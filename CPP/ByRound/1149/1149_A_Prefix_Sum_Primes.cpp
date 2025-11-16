// Problem: CF 1149 A - Prefix Sum Primes
// https://codeforces.com/contest/1149/problem/A

/*
 * Problem: Prefix Sum Primes
 * Algorithm: Greedy approach to maximize number of prime prefix sums
 * 
 * Approach:
 * - The key insight is that we want to place numbers such that prefix sums
 *   are more likely to be prime.
 * - Since we only have 1s and 2s, we can think about the pattern:
 *   - Start with 1 to get prefix sum 1 (not prime), then add 1s to get 2, 3, 5, 7, ...
 *   - Add 2s carefully to avoid producing composite numbers.
 * - Strategy:
 *   - Place all 2s first (if any), to get early sums like 2, 4, 6, ...
 *   - Then put 1s to make sums like 3, 4, 5, etc., which are more likely to be prime.
 *   - To maximize primes, placing 2 first, then 1s, and finally remaining 2s seems optimal.
 *   - But the actual greedy solution arranges it as:
 *     1. If there are 2s, place one 2 first
 *     2. Place one 1 after (to make sum 3, which is prime)
 *     3. Place all remaining 2s
 *     4. Place remaining 1s
 * 
 * Time Complexity: O(n) - single pass through input and output
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long ones(0), twos(0);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ones += (x == 1);   // Count occurrences of 1
    twos += (x == 2);   // Count occurrences of 2
  }
  if (twos) {
    printf("2 ");       // Place one 2 if available to start the sequence
    --twos;             // Decrement count of 2s used
  }
  if (ones) {
    printf("1 ");       // Place one 1 to ensure next prefix sum is 3 (prime)
    --ones;             // Decrement count of 1s used
  }
  while (twos--) {
    printf("2 ");       // Place remaining 2s
  }
  while (ones--) {
    printf("1 ");       // Place remaining 1s
  }
  puts("");             // Print newline at end
  return 0;
}


// https://github.com/VaHiX/CodeForces/