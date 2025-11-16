// Problem: CF 1004 B - Sonya and Exhibition
// https://codeforces.com/contest/1004/problem/B

/*
Flower Box:
Purpose: This code solves the problem of arranging roses (0) and lilies (1) in a row 
         to maximize the total beauty of given segments. The beauty of a segment 
         is defined as the product of the count of roses and lilies in that segment.

Algorithms/Techniques: 
- Greedy approach based on alternating pattern
- The key insight is that we can assign flowers to maximize the product of counts in each segment
- Since segments can overlap, a simple alternating pattern (0101...) works well in many cases
- This approach assumes optimal solution favors near equal distribution of types in overlapping regions

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  for (long p = 0; p < n; p++) {
    // Alternate between '0' and '1' based on index parity
    putchar(p & 1 ? '1' : '0');
  }
  puts(""); // Print newline at the end
  return 0;
}


// https://github.com/VaHiX/CodeForces/