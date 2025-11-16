// Problem: CF 1244 A - Pens and Pencils
// https://codeforces.com/contest/1244/problem/A

/*
 * Problem: Pens and Pencils
 * 
 * Purpose: Determine how many pens and pencils Polycarp should take to attend all lectures and practical classes,
 *          given constraints on writing implements capacity and usage.
 * 
 * Approach:
 * - Calculate minimum number of pens needed: ceil(a / c), since one pen can write c lectures.
 * - Calculate minimum number of pencils needed: ceil(b / d), since one pencil can handle d practical classes.
 * - Check if total implements (x + y) fit in the pencilcase (k).
 * - If not, output -1. Otherwise, output the calculated x and y.
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each case processes a constant number of operations.
 * Space Complexity: O(1), only using a fixed amount of variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d, k;
    scanf("%ld %ld %ld %ld %ld", &a, &b, &c, &d, &k);
    // Calculate minimum number of pens required (ceil(a / c))
    long x = (a + c - 1) / c;
    // Calculate minimum number of pencils required (ceil(b / d))
    long y = (b + d - 1) / d;
    // Check if total implements exceed the capacity of the pencilcase
    if (x + y > k) {
      puts("-1");
      continue;
    }
    // Output the number of pens and pencils needed
    printf("%ld %ld\n", x, y);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/