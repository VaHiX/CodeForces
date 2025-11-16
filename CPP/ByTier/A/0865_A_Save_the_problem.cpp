// Problem: CF 865 A - Save the problem!
// https://codeforces.com/contest/865/problem/A

/*
 * Problem: Generate a test case for the coin change problem such that the number of ways to make change equals the given number A.
 * 
 * Algorithm/Techniques:
 * - This solution uses a mathematical shortcut.
 * - For coins 1 and 2, the number of ways to make an amount n is n + 1.
 *   This is because we can use 0 to n coins of 1-cent denomination, and the rest is filled with 2-cent coins.
 *   For example: To make 3 cents with coins 1 and 2, we can have:
 *   - 3×1 + 0×2
 *   - 1×1 + 1×2
 *   - 0×1 + 1×2
 *   This gives us 4 ways, which is 3 + 1.
 *   Hence, to get exactly A ways, we set the amount to (2 * A - 1), using coins 1 and 2.
 * 
 * Time Complexity: O(1) - Constant time operation.
 * Space Complexity: O(1) - No extra space used.
 */

#include <cstdio>
int main() {
  long a;
  scanf("%ld", &a);
  printf("%ld 2\n1 2\n", 2 * a - 1);  // Output the required amount and coin denominations
  return 0;
}


// https://github.com/VaHiX/CodeForces/