// Problem: CF 2038 L - Bridge Renovation
// https://codeforces.com/contest/2038/problem/L

/*
L. Bridge Renovation
Purpose: Calculate the minimum number of 60-unit planks needed to cover three bridges with widths 18, 21, and 25 units,
         where each bridge requires n planks of its respective width.

Algorithms/Techniques: Greedy approach with mathematical optimization.
Time Complexity: O(1) - The algorithm performs a fixed number of operations regardless of n.
Space Complexity: O(1) - Only a constant amount of extra space is used.

Input: Single integer n (1 ≤ n ≤ 1000)
Output: Minimum number of 60-unit planks required.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  if (n == 1) {
    puts("2");   // Special case: 1 plank each bridge requires at least 2 full planks
    return 0;
  }
  long a(n), b(n), c(n);   // a, b, c represent the number of planks needed for each bridge
  long res(n / 2);         // Initialize result with n/2 (approximation of how many full planks are needed)
  b %= 2;                  // Modulo operation to check if n is odd
  a -= (n / 2);            // Reduce a by n/2
  if (b) {                 // If n was odd
    ++res;                 // Increment result since we need an extra plank
    a -= 2;                // Adjust remaining planks after subtracting two for handling odd case
  }
  if (a) {                 // If there are remaining planks to be handled
    res += (a / 3);        // Add how many full sets of three we can make
    a %= 3;                // Update a with the remainder after dividing by 3
  }
  res += (a + c + 1) / 2;  // Final calculation for remaining planks needed
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/