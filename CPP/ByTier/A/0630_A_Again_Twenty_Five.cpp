// Problem: CF 630 A - Again Twenty Five!
// https://codeforces.com/contest/630/problem/A

/*
 * Problem: A. Again Twenty Five!
 * Purpose: Calculate the last two digits of 5^n for a given n
 * Algorithm: Mathematical observation
 * 
 * Key Insight: For any n >= 2, 5^n always ends with 25
 * This is because:
 * - 5^2 = 25
 * - 5^3 = 125 (ends with 25)
 * - 5^4 = 625 (ends with 25)
 * - And so on...
 * 
 * This pattern occurs because 5^2 = 25, and multiplying by 5
 * always preserves the last two digits as 25 when n >= 2.
 * 
 * Time Complexity: O(1) - constant time operation
 * Space Complexity: O(1) - constant space usage
 */

#include <cstdio>
int main() {
  puts("25");  // Since 5^n always ends with 25 for n >= 2, we can directly output "25"
  return 0;
}


// https://github.com/VaHiX/CodeForces/