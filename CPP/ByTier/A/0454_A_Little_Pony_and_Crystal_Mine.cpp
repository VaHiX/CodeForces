// Problem: CF 454 A - Little Pony and Crystal Mine
// https://codeforces.com/contest/454/problem/A

/*
 * Problem: Little Pony and Crystal Mine
 * Description: Given an odd integer n, draw a crystal of size n x n where a diamond is inscribed.
 *              The diamond is represented by 'D', and the rest by '*'.
 * 
 * Algorithm/Technique: 
 *   - For each row, calculate how many leading/trailing '*' are needed.
 *   - The number of 'D' characters increases toward the center and decreases outward.
 *   - The symmetry is exploited by using the minimum of row index and (n-1-row).
 * 
 * Time Complexity: O(n^2) - We iterate through n rows and for each row, we print a constant number of characters.
 * Space Complexity: O(1) - Only using a constant amount of extra space (variables), not counting output.
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d\n", &n);
  for (int row = 0; row < n; row++) {
    // Determine the symmetry point: how far we are from the center
    int sym = (row < n - 1 - row) ? row : (n - 1 - row);
    // Print leading asterisks
    for (int p = 0; p < (n - 1) / 2 - sym; p++) {
      printf("*");
    }
    // Print the D's for the current row
    for (int p = 0; p < 2 * sym + 1; p++) {
      printf("D");
    }
    // Print trailing asterisks
    for (int p = 0; p < (n - 1) / 2 - sym; p++) {
      printf("*");
    }
    puts(""); // Move to next line
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/