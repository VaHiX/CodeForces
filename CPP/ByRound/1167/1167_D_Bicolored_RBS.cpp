// Problem: CF 1167 D - Bicolored RBS
// https://codeforces.com/contest/1167/problem/D

/*
 * Problem: D. Bicolored RBS
 * 
 * Algorithm/Technique: Greedy Assignment
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * Approach:
 * - Traverse the RBS from left to right.
 * - For each '(' we assign it to the color (0 or 1) based on the current value of 'open'.
 * - Toggle the 'open' variable after each assignment.
 * - For each ')' we assign it to the color (0 or 1) based on the current value of 'close'.
 * - Toggle the 'close' variable after each assignment.
 * 
 * This greedy approach ensures that we minimize the maximum nesting depth of the two subsequences
 * by fairly distributing the brackets to avoid deep nesting in either subsequence.
 */

#include <stdio.h>
#include <iostream>

int main() {
  long n;
  scanf("%ld\n", &n);
  int open(0), close(0);  // open and close represent the current color (0 or 1) to assign
  for (long p = 0; p < n; p++) {
    char x;
    scanf("%c", &x);
    if (x == '(') {
      printf("%d", open);  // print the color (0 or 1) for this '('
      open = 1 - open;    // toggle the color for next '('
    } else {
      printf("%d", close);  // print the color (0 or 1) for this ')'
      close = 1 - close;   // toggle the color for next ')'
    }
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/