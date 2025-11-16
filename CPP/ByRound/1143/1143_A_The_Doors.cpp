// Problem: CF 1143 A - The Doors
// https://codeforces.com/contest/1143/problem/A

/*
 * Problem: A. The Doors
 * Purpose: Find the smallest index k such that after opening the first k doors,
 *          all doors in at least one exit are open, allowing Mr. Black to exit.
 * Algorithms/Techniques: Single pass iteration with tracking of last door positions.
 * Time Complexity: O(n), where n is the number of doors.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long left(0), right(0);  // Track the last position of door in left and right exits
  for (long p = 1; p <= n; p++) {  // Iterate through each door in order
    long x;
    scanf("%ld", &x);
    if (x == 0) {
      left = p;  // Update the last position of a left exit door
    } else {
      right = p;  // Update the last position of a right exit door
    }
  }
  printf("%ld\n", left < right ? left : right);  // Output the earliest index where all doors in either exit are open
  return 0;
}


// https://github.com/VaHiX/codeForces/