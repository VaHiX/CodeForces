// Problem: CF 1250 L - Divide The Students
// https://codeforces.com/contest/1250/problem/L

/*
L. Divide The Students

Algorithm: Greedy approach with careful distribution of students to minimize the maximum subgroup size.
The goal is to partition a group of students (a Assembler fans, b Basic fans, c C++ fans) into 3 subgroups such that,
no subgroup contains both Assembler and C++ fans.

Approach:
1. Initially compute a naive estimate m = (a + b + c + 2) / 3 (rounding up).
2. If there are conflicts (i.e., either a >= b or c >= b), we attempt to re-allocate.
3. We sort a, c so that a >= c.
4. Adjust the value of b accordingly to avoid conflict in subgroup with maximum size.
5. Return the final answer as max(m, (a + b + 1) / 2).

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input:
- t test cases
- For each test case: three integers a, b, c

Output:
- Minimum possible size of the largest subgroup.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long m = (a + b + c + 2) / 3; // Initial guess for minimal max subgroup size
    long ans = m;
    if (a >= b || c >= b) { // If there's a conflict between a and b or c and b
      if (a < c) { // Ensure a >= c
        long tmp = c;
        c = a;
        a = tmp;
      }
      if (c < m) { // Adjust b to reduce the conflict
        b -= (m - c);
        b = (b > 0) ? b : 0; // Ensure b doesn't go below zero
      }
      m = (m > c) ? m : c; // Max of current m and c (updated max size)
      long x = (a + b + 1) / 2; // Alternative max size for two groups
      ans = (m > x) ? m : x; // Final answer is the maximum of both
    }
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/