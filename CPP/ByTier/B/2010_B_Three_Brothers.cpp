// Problem: CF 2010 B - Three Brothers
// https://codeforces.com/contest/2010/problem/B

#include <cstdio>
/**
 * B. Three Brothers
 * 
 * Problem Description:
 * Three brothers numbered 1 (oldest), 2 (middle), and 3 (youngest) agreed to meet.
 * Given the numbers of two brothers who arrived on time, determine which brother was late.
 * 
 * Algorithm:
 * - Read two integers representing brothers who arrived on time
 * - Ensure x <= y by swapping if necessary
 * - Use conditional logic to determine the missing brother number
 * 
 * Time Complexity: O(1) - Constant time operations
 * Space Complexity: O(1) - Only using a constant amount of extra space
 */
int main() {
  int x, y;
  scanf("%d %d", &x, &y);
  // Ensure x is the smaller number and y is the larger number
  if (x > y) {
    int z = x;
    x = y;
    y = z;
  }
  // Check all possible cases of which brothers arrived on time
  if (x == 1 && y == 2) {
    puts("3"); // Brother 3 was late
  } else if (x == 1 && y == 3) {
    puts("2"); // Brother 2 was late
  } else if (x == 2 && y == 3) {
    puts("1"); // Brother 1 was late
  } else {
    puts("ERROR"); // Invalid input
  }
}

// https://github.com/VaHiX/codeForces/