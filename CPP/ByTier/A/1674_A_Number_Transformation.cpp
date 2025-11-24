// Problem: CF 1674 A - Number Transformation
// https://codeforces.com/contest/1674/problem/A

/*
 * Problem: Number Transformation
 * 
 * Given integers x and y, find positive integers a and b such that applying
 * the operation "x = b * x" exactly a times results in x becoming y.
 * 
 * Approach:
 * - If y is not divisible by x, then it's impossible to achieve y from x
 *   using multiplication by a positive integer b.
 * - Otherwise, we can set a = 1 and b = y / x.
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * Algorithms/Techniques: Modular arithmetic, simple division check
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    if (y % x) { // Check if y is divisible by x
      puts("0 0"); // No valid pair exists
    } else {
      printf("1 %ld\n", y / x); // Set a = 1, b = y/x
    }
  }
}


// https://github.com/VaHiX/CodeForces/