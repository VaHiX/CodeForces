// Problem: CF 804 A - Find Amir
// https://codeforces.com/contest/804/problem/A

/*
 * Code Purpose: Find the minimum cost to visit all schools in a linear arrangement
 *               where tickets can be bought between adjacent schools.
 * 
 * Algorithm: Mathematical approach
 *            - Since we can start at any school and visit all schools,
 *              we can think of this as a path that needs to cover n schools
 *              with minimum ticket cost.
 *            - The optimal strategy is to buy tickets for n-1 adjacent pairs
 *              and the minimum cost will be (n-1)/2 when tickets are reused optimally.
 * 
 * Time Complexity: O(1) - Only simple arithmetic operations
 * Space Complexity: O(1) - Only one variable is used
 */

#include <cstdio>
int main() {
  long n;                    // Variable to store number of schools
  scanf("%ld", &n);          // Read input number of schools
  printf("%ld\n", (n - 1) / 2);  // Calculate and print minimum cost
  return 0;                  // End of program
}


// https://github.com/VaHiX/CodeForces/