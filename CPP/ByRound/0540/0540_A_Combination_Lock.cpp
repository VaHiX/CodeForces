// Problem: CF 540 A - Combination Lock
// https://codeforces.com/contest/540/problem/A

/*
Purpose: 
  This program calculates the minimum number of moves required to align a combination lock 
  from its initial state to the target combination. Each disk can be rotated forward or 
  backward, and movement wraps around from 0 to 9 and vice versa. The optimal path between 
  two digits is the minimum of the clockwise and counter-clockwise distances.

Algorithms/Techniques:
  - For each digit position, compute the absolute difference between initial and target digits.
  - Since digits wrap around (0-9), the shortest distance is the minimum of:
    - Direct difference (e.g., 1 to 5 = 4)
    - Wrap-around distance (e.g., 1 to 5 wraps around as 9-5+1 = 5)
  - Sum up all the minimum distances for all positions.

Time Complexity: O(n), where n is the length of the combination string.
Space Complexity: O(1), excluding input storage which is O(n) but not counted in the auxiliary space.

*/
#include <cstdio>
#include <iostream>
#include <string>

int main() {
  const int N = 10; // Number of digits on the lock (0 through 9)
  int digits;
  scanf("%d\n", &digits); // Read number of disks
  std::string initial;
  getline(std::cin, initial); // Read initial state of the lock
  std::string final;
  getline(std::cin, final); // Read target combination
  int moves(0); // Initialize total moves counter
  for (int p = 0; p < digits; p++) {
    int diff = initial[p] - final[p]; // Calculate difference between digits
    if (diff < 0) {
      diff = -diff; // Take absolute value
    }
    if (diff > N / 2) {
      diff = N - diff; // Choose the shorter path (clockwise vs counter-clockwise)
    }
    moves += diff; // Accumulate minimum moves for current digit
  }
  printf("%d\n", moves); // Output the total minimum moves required
  return 0;
}


// https://github.com/VaHiX/CodeForces/