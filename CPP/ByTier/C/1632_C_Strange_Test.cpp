// Problem: CF 1632 C - Strange Test
// https://codeforces.com/contest/1632/problem/C

/*
C. Strange Test
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Problem Description:
Given two integers a and b where a < b, we need to find the minimum number of operations to make a equal to b.
Operations allowed:
1. a := a + 1
2. b := b + 1
3. a := a | b (bitwise OR)

The solution uses a brute-force approach over the range [a, b) to evaluate each value x as a potential candidate for minimizing the operations.

Algorithms/Techniques:
- Brute-force search within the interval [a, b)
- Bit manipulation using XOR and right shift to analyze bit differences
- Greedy optimization for calculating minimal steps

Time Complexity: O((b - a) * log(max(a, b)))
Space Complexity: O(1)

Note: The actual optimal solution relies on understanding the behavior of OR operations and bit patterns, but this code implements a brute-force simulation.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long ans(b - a); // Initialize with the cost of increasing 'a' to 'b'
    for (long x = a; x < b; x++) { // Iterate through all values from a to b-1
      long y(0); // This will store the modified value of b for this iteration
      for (long p = 21; p >= 0; p--) { // Check all bits up to 21st bit (enough for numbers up to 1e6)
        if ((b >> p) & 1) { // If current bit in 'b' is set
          y ^= (1 << p); // XOR with this bit in y
        } else if ((x >> p) & 1) { // Else if current bit in 'x' is set
          y ^= (1 << p); // Set the same bit in y and exit loop since we have found a match
          break;
        }
      }
      long tst = (x - a) + (x | y) - b + 1; // Compute a temporary cost for this x
      ans = (ans < tst ? ans : tst); // Update minimum if current is smaller
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/