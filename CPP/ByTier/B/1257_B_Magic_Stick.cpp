// Problem: CF 1257 B - Magic Stick
// https://codeforces.com/contest/1257/problem/B

/*
B. Magic Stick

Purpose:
This program determines whether a given number y can be obtained from another number x using two specific spells:
1. If x is even, it becomes 3*x/2.
2. If x > 1, it becomes x-1.

The approach checks for special cases based on the value of x and y to determine if transformation is possible without simulation.

Algorithms/Techniques:
- Case analysis and mathematical reasoning
- Direct checking instead of simulation
- Greedy or heuristic logic for transformations

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input Format:
First line contains T (number of test cases).
Each test case has two integers x and y.

Output Format:
For each test case, print "YES" if y can be obtained from x using the spells, otherwise "NO".
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    bool ans(true); // Initialize result as true
    if (x == 1) {
      ans = (y == 1); // Only 1 can produce 1
    } else if (x == 2 || x == 3) {
      ans = (y <= 3); // x=2 or 3 can only reach up to 3
    }
    puts(ans ? "YES" : "NO"); // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/