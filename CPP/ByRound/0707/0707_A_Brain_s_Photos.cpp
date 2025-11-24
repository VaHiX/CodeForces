// Problem: CF 707 A - Brain's Photos
// https://codeforces.com/contest/707/problem/A

/*
 * Purpose: Determine if a photo is colored or black-and-white based on pixel colors.
 * Algorithm: 
 *   - Read the photo dimensions n and m.
 *   - Iterate through each pixel of the photo.
 *   - If any pixel is 'C', 'M', or 'Y', mark the photo as colored and stop checking.
 *   - Otherwise, if all pixels are only 'W', 'G', or 'B', it's black-and-white.
 * 
 * Time Complexity: O(n * m) - We may need to examine every pixel in the worst case.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m;
  std::cin >> n >> m;
  bool color(false); // Flag to track if any colored pixel is found
  for (int row = 0; row < n; row++) {
    if (color) {
      break; // Early exit if color is already detected
    }
    for (int col = 0; col < m; col++) {
      char x;
      std::cin >> x;
      if (x == 'C' || x == 'M' || x == 'Y') {
        color = true; // Found a colored pixel
        break;
      }
    }
  }
  std::cout << (color ? "#Color" : "#Black&White") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/