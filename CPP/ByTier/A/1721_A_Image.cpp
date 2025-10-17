// Problem: CF 1721 A - Image
// https://codeforces.com/contest/1721/problem/A

/*
 * Problem: Minimum Moves to Make All Pixels Same Color (2x2 Image)
 *
 * Description:
 * Given a 2x2 grid of pixels where each pixel has one of 26 possible colors,
 * determine the minimum number of moves required to make all pixels the same color.
 * Each move allows painting up to two identical-colored pixels into a different color.
 *
 * Algorithm:
 * - Count frequency of each color in the 2x2 grid (26 possible colors).
 * - Based on the maximum frequency and number of colors appearing twice:
 *   - If max frequency is 1: all colors are unique => need 3 moves
 *   - If max frequency is 4: already all same color => 0 moves
 *   - If max frequency is 3 or two colors appear twice => 1 move
 *   - Otherwise => 2 moves
 *
 * Time Complexity: O(1) per test case since grid size is fixed (2x2)
 * Space Complexity: O(1) as we use fixed-size arrays (26 elements for counting)
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::vector<std::string> sv(2); // Store the two rows of the 2x2 grid
    for (long p = 0; p < 2; p++) {
      std::cin >> sv[p];
    }
    std::vector<long> cv(26, 0); // Count frequency of each color (a-z)
    long mx(0), two(0); // mx = max count of any color, two = number of colors appearing twice
    for (long p = 0; p < 2; p++) {
      for (long q = 0; q < 2; q++) {
        long x = sv[p][q] - 'a'; // Convert character to index 0-25
        ++cv[x]; // Increment count of that color
        if (cv[x] == 2) {
          ++two; // Track how many colors appear exactly twice
        }
        mx = (mx > cv[x]) ? mx : cv[x]; // Update maximum frequency
      }
    }
    if (mx == 1) {
      puts("3"); // All four pixels have different colors => need 3 moves
    } else if (mx == 4) {
      puts("0"); // All pixels are the same color => no moves needed
    } else if (two == 2 || mx == 3) {
      puts("1"); // Either two pairs of identical colors or one color appears three times => 1 move
    } else {
      puts("2"); // Otherwise => 2 moves required
    }
  }
}


// https://github.com/VaHiX/codeForces/