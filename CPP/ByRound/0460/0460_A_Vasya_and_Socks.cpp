// Problem: CF 460 A - Vasya and Socks
// https://codeforces.com/contest/460/problem/A

/*
 * Problem: Vasya and Socks
 * 
 * Purpose: 
 *   Determine how many consecutive days Vasya can wear socks before running out.
 *   - Initially, Vasya has 'n' pairs of socks.
 *   - Each day, he wears one pair.
 *   - Every 'm'-th day (m, 2m, 3m, ...), his mom buys him a new pair of socks.
 *   - The new socks are available the next day.
 * 
 * Algorithms/Techniques:
 *   - Simulation approach: Iterate day by day until socks run out.
 *   - On each day, check if it's a buying day (multiple of m), and if not,
 *     decrement the sock count.
 * 
 * Time Complexity: O(n + n/m)
 *   - In worst case, Vasya uses all his initial socks and then gets new socks
 *     every m days until he runs out again.
 * 
 * Space Complexity: O(1)
 *   - Only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  int socks, interval;
  scanf("%d %d\n", &socks, &interval);
  int day = 0;
  while (true) {
    ++day;
    if (socks <= 0) {  // If no socks left, stop the simulation
      break;
    }
    if (day % interval) {  // If not a buying day (i.e., day is not divisible by interval)
      --socks;  // Use a pair of socks
    }
    // On buying days, no decrement occurs, so new socks are added next day
  }
  printf("%d\n", day - 1);  // Return the last day number where socks were used
  return 0;
}


// https://github.com/VaHiX/CodeForces/