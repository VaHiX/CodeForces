// Problem: CF 1366 A - Shovels and Swords
// https://codeforces.com/contest/1366/problem/A

/*
 * Problem: A. Shovels and Swords
 * Purpose: Determine the maximum number of emeralds Polycarp can earn by crafting shovels and swords
 *          from given sticks and diamonds.
 * 
 * Algorithms/Techniques:
 *   - Greedy approach with mathematical optimization
 *   - Case analysis based on the ratio of sticks to diamonds
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each test case takes constant time.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long ans(0);
    if (a < b) {
      long x = a;
      a = b;
      b = x;
    }
    // If sticks are more than twice the diamonds, we can use all diamonds to make swords
    if (a > 2 * b) {
      ans = b;
    } else {
      // Otherwise, find optimal balance between shovels and swords
      long diff = a - b;
      a -= 2 * diff;
      b -= diff;
      ans = diff + (2 * b / 3);
    }
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/