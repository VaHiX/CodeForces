// Problem: CF 465 A - inc ARG
// https://codeforces.com/contest/465/problem/A

/*
 * Purpose: This program determines how many bits in a binary cell will change
 *          when 1 is added to the value represented by the cell.
 *          
 *          The cell stores bits in reverse order (least significant bit first).
 *          The algorithm simulates the addition of 1 and counts how many bits
 *          flip from their initial state.
 *          
 * Algorithm: 
 *          - Traverse the bits from least significant to most significant.
 *          - Count consecutive '1's starting from the least significant bit.
 *          - If there's a '0' encountered, the carry stops and one more bit flips.
 *          - If all bits are '1', we carry over to the next position (which wraps around).
 *          
 * Time Complexity: O(n) where n is the number of bits in the cell.
 * Space Complexity: O(n) for storing the input string of bits.
 */
#include <cstdio>
#include <iostream>
#include <string>

int main() {
  int n;
  scanf("%d\n", &n);
  std::string bits;
  getline(std::cin, bits);
  int output = 0;
  // Traverse from least significant bit (index 0) to most significant bit (index n-1)
  for (int p = 0; p < bits.size(); p++) {
    // If bit is '1', it will flip due to carry propagation
    if (bits[p] == '1') {
      ++output;
    } else {
      // If bit is '0', carry stops and one more bit flips (the '0' becomes '1')
      break;
    }
  }
  // If not all bits were '1', we must add one more to account for the final carry
  if (output < n) {
    ++output;
  }
  printf("%d\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/