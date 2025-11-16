// Problem: CF 1669 A - Division?
// https://codeforces.com/contest/1669/problem/A

/*
 * Code Purpose: Determine the division of a Codeforces user based on their rating.
 *               Uses a series of conditional checks to map the rating to a division.
 *
 * Algorithms/Techniques: 
 *   - Simple conditional logic (if-else chain) to compare the rating against thresholds.
 *   - Direct mapping of rating ranges to division numbers.
 *
 * Time Complexity: O(1) - Each test case performs a constant number of comparisons.
 * Space Complexity: O(1) - Only a fixed amount of additional space is used (variables t, r, res).
 */

#include <cstdio>
int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) { // Process each test case
    long r; // Current user's rating
    scanf("%ld", &r);
    int res(1); // Initialize result division as 1 (highest division)
    if (r <= 1399) { // If rating is at most 1399, it's Division 4
      res = 4;
    } else if (r <= 1599) { // If rating is between 1400 and 1599, it's Division 3
      res = 3;
    } else if (r <= 1899) { // If rating is between 1600 and 1899, it's Division 2
      res = 2;
    } else if (1900 <= r) { // If rating is 1900 or more, it's Division 1
      res = 1;
    }
    printf("Division %d\n", res); // Output the determined division
  }
}


// https://github.com/VaHiX/CodeForces/