// Problem: CF 725 B - Food on the Plane
// https://codeforces.com/contest/725/problem/B

/*
 * Purpose: Calculate the number of seconds Vasya has to wait until he gets his lunch.
 * 
 * Approach:
 * - The flight attendants serve rows in a specific pattern with alternating move distances (2, 1, 3, 1, ...).
 * - Each row takes 6 seconds to serve (one second per seat).
 * - The order of serving is: right side (f, e, d) then left side (a, b, c).
 * - The pattern of rows served by the first attendant is: 1, 2, 5, 6, 9, 10, ...
 * - For any given row n, calculate how many complete cycles have passed and how many seconds
 *   are needed to reach that row, and then determine the position of seat s in the row.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long long row;           // Row number of Vasya's seat
  char col;                // Column (seat) of Vasya's seat
  
  scanf("%lld%c", &row, &col);  // Read input

  // Compute the time:
  // ((row - 1) / 4) * 16: Number of complete 4-row chunks, each contributes 16 seconds
  // ((row % 2 == 0) ? 7 : 0): Add adjustment based on whether row is even or odd
  // ((col > 'c') ? ('g' - col) : (col - 'a' + 4)): Position of seat in the row relative to serving order
  printf("%lld", ((row - 1) / 4) * 16 + ((row % 2 == 0) ? 7 : 0) +
                     ((col > 'c') ? ('g' - col) : (col - 'a' + 4)));

  return 0;
}


// https://github.com/VaHiX/CodeForces/