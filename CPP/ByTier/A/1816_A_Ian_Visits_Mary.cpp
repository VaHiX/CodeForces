// Problem: CF 1816 A - Ian Visits Mary
// https://codeforces.com/contest/1816/problem/A

/*
 * Problem: Ian Visits Mary
 * Purpose: Find a path from (0,0) to (a,b) in at most 2 jumps, such that each jump
 *          is a direct line segment between lattice points with no other lattice
 *          points on the segment.
 *
 * Algorithm:
 * - If the greatest common divisor (gcd) of a and b is 1, then (0,0) and (a,b)
 *   are directly connected without any intermediate lattice points. So, one jump is sufficient.
 * - Otherwise, we use two jumps:
 *   - First jump: (0,0) -> (a-1, 1)
 *   - Second jump: (a-1, 1) -> (a, b)
 *
 * Time Complexity: O(log(min(a, b))) per test case due to GCD computation.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

#include <cstdio>

// Function to compute the greatest common divisor (gcd) of two numbers
long gcd(long a, long b) { 
    return (b == 0) ? a : gcd(b, a % b); 
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (gcd(a, b) == 1) {
      // If gcd(a,b) == 1, then (0,0) and (a,b) are coprime, so one direct jump is possible
      printf("1\n%ld %ld\n", a, b);
    } else {
      // Otherwise, use two jumps
      printf("2\n%ld %ld\n%ld %ld\n", a - 1, 1, a, b);
    }
  }
}


// https://github.com/VaHiX/CodeForces/