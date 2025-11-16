// Problem: CF 748 A - Santa Claus and a Place in a Class
// https://codeforces.com/contest/748/problem/A

/*
Code Purpose:
This program determines the position of Santa Claus in a classroom based on his assigned seat number.
The classroom has n lanes, each with m desks, and each desk has two seats (left and right).
Seats are numbered sequentially across lanes, starting from the one closest to the blackboard.
The algorithm computes which lane, desk, and side (left or right) corresponds to the given seat number k.

Algorithms/Techniques:
- Modular arithmetic to map a linear index to 2D coordinates
- Integer division and modulo operations for coordinate calculation

Time Complexity: O(1) - Constant time computation using arithmetic operations.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

#include <iostream>
int main() {
  long n, m, k;
  std::cin >> n >> m >> k;
  --k;  // Convert to 0-based indexing
  
  // Determine the lane (column) by dividing by total number of seats per lane
  long col = k / (2 * m);
  
  // Determine the desk (row) within the lane
  long row = (k % (2 * m)) / 2;
  
  // Determine if the seat is on the left ('L') or right ('R') side
  char side = (k % 2) ? 'R' : 'L';
  
  // Output 1-based lane, desk, and side
  std::cout << (1 + col) << " " << (1 + row) << " " << side << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/