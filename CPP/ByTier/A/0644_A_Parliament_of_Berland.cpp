// Problem: CF 644 A - Parliament of Berland
// https://codeforces.com/contest/644/problem/A

/*
 * Problem: Parliament of Berland
 * 
 * Purpose: Assign parliamentarians to seats in a rectangular hall such that no two
 *          parliamentarians from the same party (Democrats or Republicans) sit adjacent.
 *          Democrats are at odd indices, Republicans at even indices.
 * 
 * Algorithm/Technique:
 * - This is a seating arrangement problem with a constraint on neighboring seats.
 * - The solution uses a pattern-based filling of the matrix:
 *   - If the number of columns is even and the row is odd, fill in reverse order.
 *   - Otherwise, fill normally from left to right.
 * - This pattern ensures minimal adjacency of same-party members.
 * 
 * Time Complexity: O(a * b)
 *   - We iterate through each cell of the a x b matrix once to assign values.
 * 
 * Space Complexity: O(a * b)
 *   - We use a 2D vector to store the seating arrangement of size a x b.
 */

#include <stdio.h>
#include <iostream>
#include <vector>

int main() {
  long n, a, b;
  std::cin >> n >> a >> b;
  if (a * b < n) {
    puts("-1");
    return 0;
  }
  std::vector<std::vector<long>> seat(a, std::vector<long>(b, 0));
  long current(0);
  for (long row = 0; row < a; row++) {
    for (long col = 0; col < b; col++) {
      ++current;
      if (current > n) {
        break;
      } else if (b % 2 == 0 && row % 2 == 1) {
        // For even columns and odd rows, fill in reverse order
        seat[row][b - 1 - col] = current;
      } else {
        // For all other cases, fill normally
        seat[row][col] = current;
      }
    }
  }
  for (long row = 0; row < a; row++) {
    for (long col = 0; col < b; col++) {
      std::cout << seat[row][col] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/