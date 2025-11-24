// Problem: CF 1950 A - Stair, Peak, or Neither?
// https://codeforces.com/contest/1950/problem/A

/*
 * Problem: A. Stair, Peak, or Neither?
 * Algorithms/Techniques: Simple conditional logic comparison
 * 
 * Time Complexity: O(t) where t is the number of test cases
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * Description: This program determines if three given digits form a "stair", "peak", or "none".
 * A stair satisfies a < b < c, a peak satisfies a < b > c, otherwise it's none.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);  // Read number of test cases
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);  // Read three digits for current test case
    if (a < b && b < c) {  // Check if it forms a stair (strictly increasing)
      puts("STAIR");
    } else if (a < b && b > c) {  // Check if it forms a peak (increasing then decreasing)
      puts("PEAK");
    } else {  // Otherwise it's neither
      puts("NONE");
    }
  }
}


// https://github.com/VaHiX/codeForces/