// Problem: CF 1790 E - Vlad and a Pair of Numbers
// https://codeforces.com/contest/1790/problem/E

/*
 * Problem: Vlad and a Pair of Numbers
 * 
 * Purpose:
 *   Given a number x = a ⊕ b, find positive integers a and b such that 
 *   x = (a + b) / 2. That is, the XOR of a and b equals the average of a and b.
 *   This implies that a + b = 2 * x, and a ⊕ b = x. 
 *   We need to find such a and b, or determine that none exist.
 * 
 * Algorithm:
 *   - The key insight is that if (a + b) / 2 = x, then a + b = 2 * x.
 *   - Also, a ⊕ b = x.
 *   - Let's test a = x / 2 and b = x + x / 2.
 *   - Then check if a + b = 2 * x and a ⊕ b = x. If so, we have a solution.
 *   - A necessary condition is that x must be even, since a + b is even.
 *   - If x is odd, there's no solution.
 * 
 * Time Complexity: O(1) per test case, as all operations are constant time.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    if (x % 2) {  // If x is odd, no solution exists since a + b must be even
      puts("-1");
      continue;
    }
    long a(x / 2), b(x + x / 2);  // Try a = x/2 and b = x + x/2
    if ((a ^ b) != x) {  // Verify that a XOR b equals x
      puts("-1");
    } else {
      printf("%ld %ld\n", a, b);  // Output the valid pair
    }
  }
}


// https://github.com/VaHiX/CodeForces/