// Problem: CF 898 B - Proper Nutrition
// https://codeforces.com/contest/898/problem/B

/*
 * Problem: Proper Nutrition
 * 
 * Given n burles, cost of one bottle of Ber-Cola (a), and cost of one Bars bar (b),
 * determine if it's possible to spend exactly n burles buying some number of bottles
 * of Ber-Cola and/or Bars bars.
 * 
 * This is essentially solving the equation: a*x + b*y = n for non-negative integers x and y.
 * 
 * Algorithm:
 * - Iterate through possible values of x (number of Ber-Cola bottles) from 0 to n/a
 * - For each x, compute the remaining amount (n - x*a)
 * - Check if this remaining amount is divisible by b
 * - If yes, then y = (n - x*a) / b, and we have a valid solution
 * 
 * Time Complexity: O(n / a)
 * Space Complexity: O(1)
 * 
 * Note: Since a and n can be up to 1e7, iteration up to n/a may still be feasible
 * as 1e7 / 1 = 1e7. A more efficient approach could use Extended Euclidean Algorithm
 * to solve the Diophantine equation, but this simple brute force works within constraints.
 */

#include <stdio.h>
#include <iostream>

int main() {
  long n, a, b;
  std::cin >> n >> a >> b;
  long x(-1), y(-1);  // Initialize x and y to -1 to indicate no solution found yet
  
  // Iterate over number of Ber-Cola bottles (x)
  for (long p = 0; p * a <= n; p++) {
    // Check if remaining amount after buying p bottles of Ber-Cola is divisible by b
    if ((n - p * a) % b == 0) {
      x = p;                        // Found valid number of Ber-Cola bottles
      y = (n - p * a) / b;          // Calculate corresponding number of Bars bars
      break;                        // Exit loop as solution found
    }
  }
  
  // Output result
  if (x >= 0) {
    printf("YES\n%ld %ld\n", x, y);
  } else {
    puts("NO");
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/