// Problem: CF 787 A - The Monster
// https://codeforces.com/contest/787/problem/A

/*
 * Problem: A. The Monster
 * 
 * Purpose: Determine the first time when Rick and Morty scream simultaneously.
 *          Rick screams at times: b + k*a
 *          Morty screams at times: d + k*c
 *          We need to find the smallest positive time where both equations yield the same value.
 * 
 * Algorithm:
 *   - This is essentially solving a linear Diophantine equation:
 *     a*x - c*y = d - b
 *   - We use the Extended Euclidean Algorithm implicitly via GCD to check solvability
 *   - Then perform a linear search to find the smallest valid solution
 * 
 * Time Complexity: O(a + c), since in worst case we may have to iterate up to max(a,c)
 * Space Complexity: O(1), only using a few variables
 */

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long a, b, c, d;
  scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
  long gcdac = gcd(a, c);  // Compute GCD of a and c to check solvability
  long target = d - b;     // RHS of equation a*x - c*y = target
  if ((target % gcdac) != 0) {  // Check if equation is solvable
    puts("-1");
    return 0;
  }
  long x(0), y(0);         // Initialize x and y for search
  while ((a * x - c * y) != target) {  // Search for a solution using brute force
    if (a * x - c * y < target) {  // If current value is less than target, increment x
      ++x;
    } else {                       // Else increment y
      ++y;
    }
  }
  printf("%ld\n", b + a * x);  // Return the time when they scream together
  return 0;
}


// https://github.com/VaHiX/CodeForces/