// Problem: CF 1575 K - Knitting Batik
// https://codeforces.com/contest/1575/problem/K

/*
K. Knitting Batik
Algorithms/Techniques: Modular exponentiation, combinatorics
Time Complexity: O(log(n*m)) due to modular exponentiation
Space Complexity: O(1)

The problem asks to count valid colorings of an n x m grid with k colors such that 
two specified r x c sub-rectangles have the same pattern. 

Key observations:
1. If the two rectangles overlap completely (ax == bx && ay == by), then all cells in the grid can be chosen freely, resulting in k^(n*m) combinations.
2. Otherwise, we must ensure that the two rectangles match exactly. This means fixing a certain number of cells equal to the area covered by one rectangle minus the overlapping area if any.

The solution computes the number of valid colorings using modular exponentiation:
- If rectangles are identical: k^(n * m) mod (MOD - 1) 
- Otherwise: k^((n * m) - (r * c)) mod (MOD - 1)
*/

#include <cstdio>
const long long MOD = 1000000007;

// Fast modular exponentiation function to compute (a^b) % c
long long POWER(long long a, long long b, long long c) {
  long long r = 1 % c;  // Initialize result with 1 mod c
  for (; b; b >>= 1) {  // Loop until b becomes zero
    if (b & 1)          // If b is odd, multiply result by a
      r = r * a % c;
    a = a * a % c;      // Square a for next iteration
  }
  return r;
}

int main() {
  int n, m, k, r, c;
  scanf("%d%d%d%d%d", &n, &m, &k, &r, &c);
  int ax, ay, bx, by;
  scanf("%d%d%d%d", &ax, &ay, &bx, &by);
  
  if (ax == bx && ay == by)
    // If rectangles are identical, all cells can be chosen freely
    printf("%lld\n", POWER(k, (long long)n * m % (MOD - 1), MOD));
  else
    // Otherwise, subtract the area of one rectangle from total to account for constraint
    printf("%lld",
           POWER(k, ((long long)n * m - (long long)r * c) % (MOD - 1), MOD));
  return 0;
}


// https://github.com/VaHiX/codeForces/