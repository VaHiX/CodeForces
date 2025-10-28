// Problem: CF 1132 A - Regular Bracket Sequence
// https://codeforces.com/contest/1132/problem/A

#include <cstdio>
// Flowerbox:
// Problem: Determine if given counts of four types of bracket strings can be ordered to form a regular bracket sequence.
// Algorithm: Greedy approach based on balance tracking and string properties.
// Time Complexity: O(1) - constant time operations.
// Space Complexity: O(1) - only using fixed amount of variables.

int main() {
  long a, b, c, d;
  scanf("%ld %ld %ld %ld", &a, &b, &c, &d); // Read counts of four bracket types
  int ans(1); // Assume answer is possible initially
  
  if (a != d) { // If opening and closing brackets don't match in count, impossible
    ans = 0;
  }
  
  if (c && !a) { // If there are ")(" strings but no "(()" strings, impossible to balance
    ans = 0;
  }
  
  printf("%d\n", ans); // Output result
  return 0;
}

// https://github.com/VaHiX/codeForces/