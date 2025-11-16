// Problem: CF 1748 F - Circular Xor Reversal
// https://codeforces.com/contest/1748/problem/F

#include <iostream>
// Flowerbox describing the code purpose, algorithms, time and space complexity
/*
Code Purpose:
This code solves the "Circular Xor Reversal" problem where we need to reverse an
array of powers of 2 using XOR operations on adjacent elements in a circular
manner. The approach uses a sequence of operations that effectively shifts
elements to their correct positions in reverse order.

Algorithms/Techniques:
- The algorithm uses a series of carefully chosen indices to perform XOR
operations.
- It constructs three segments of operations to achieve the reversal:
  1. First segment to prepare the array.
  2. Second segment to move elements to their final positions.
  3. Third segment to clean up and finalize the reversed array.

Time Complexity: O(n^2) - worst case due to nested loops in the operation
generation. Space Complexity: O(n) - for storing the sequence of operations.

*/
int rs[300013], t = 0, n, i;
void o(int l, int r) {
  int l_ = l, r_ = --r;
  while (l <= r) {
    for (i = r - 1; i >= l; i--)
      rs[++t] = i % n; // Store indices in reverse order to shift elements
    for (i = l + 1; i < r; i++)
      rs[++t] = i % n; // Store indices in normal order
    l++, r--;          // Move inward
  }
  for (i = l_; i < (l_ + r_) / 2; i++)
    rs[++t] = i % n; // Additional operations to finalize
}
int main() {
  std::cin >> n;
  o(0, n), o((n + 1) / 2, n / 2 + n), o(0, n); // Call operations in sequence
  for (std::cout << t << '\n', i = 1; i <= t; i++)
    std::cout << rs[i] << ' '; // Output all operations
}

// https://github.com/VaHiX/CodeForces/