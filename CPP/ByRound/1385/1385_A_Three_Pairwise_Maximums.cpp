// Problem: CF 1385 A - Three Pairwise Maximums
// https://codeforces.com/contest/1385/problem/A

/*
Purpose: This code solves the problem of finding three positive integers a, b, and c such that 
         x = max(a, b), y = max(a, c), and z = max(b, c). It determines whether such a solution exists,
         and if so, outputs one valid set of a, b, c.

Algorithms/Techniques:
- Greedy approach with case analysis
- The solution checks all possible arrangements of the maximums to determine feasibility

Time Complexity: O(1) - constant time per test case, as there's a fixed number of comparisons and operations
Space Complexity: O(1) - only a constant amount of extra space is used

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, z;
    scanf("%ld %ld %ld", &x, &y, &z);
    if (x == y && x >= z) {
      // If x equals y and x is greater than or equal to z, we can assign a=x, b=z, c=z
      printf("YES\n%ld %ld %ld\n", x, z, z);
    } else if (x == z && z >= y) {
      // If x equals z and z is greater than or equal to y, we can assign a=x, b=y, c=y
      printf("YES\n%ld %ld %ld\n", x, y, y);
    } else if (y == z && y >= x) {
      // If y equals z and y is greater than or equal to x, we can assign a=x, b=y, c=x
      printf("YES\n%ld %ld %ld\n", y, x, x);
    } else {
      // If none of the above conditions hold, it's impossible to find such a, b, c
      puts("NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/