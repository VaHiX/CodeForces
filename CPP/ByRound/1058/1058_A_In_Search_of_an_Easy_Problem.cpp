// Problem: CF 1058 A - In Search of an Easy Problem
// https://codeforces.com/contest/1058/problem/A

/*
 * Problem: A. In Search of an Easy Problem
 * Purpose: Determine if a problem is easy or hard based on responses from n people.
 *          If any person thinks the problem is hard (input 1), output "HARD".
 *          Otherwise, output "EASY".
 * 
 * Algorithm/Techniques:
 * - Single pass through input to check for any '1' (hard).
 * - Early termination when a '1' is found.
 * 
 * Time Complexity: O(n) where n is the number of people
 * Space Complexity: O(1) - only using a constant amount of extra space
 */

#include <cstdio>
int main() {
  int x = 0;  // Flag to indicate if any person thinks the problem is hard
  scanf("%d");  // Read n (number of people), but don't store it since we don't need it
  while (!x && scanf("%d", &x) > 0)  // Continue reading inputs until x becomes 1 or EOF
    ;  // Empty loop body
  printf(x ? "HARD" : "EASY");  // Print result based on value of x
}


// https://github.com/VaHiX/codeForces/