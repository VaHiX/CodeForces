// Problem: CF 523 A - Rotate, Flip and Zoom
// https://codeforces.com/contest/523/problem/A

/*
 * Code Purpose:
 * This program performs three transformations on a monochrome image:
 * 1. Rotate 90 degrees clockwise
 * 2. Flip horizontally
 * 3. Zoom in 2x (double the linear sizes)
 *
 * Algorithm/Techniques:
 * - The image is processed directly by mapping each output pixel to the corresponding input pixel.
 * - For the rotation and flip combination followed by zoom, we map the final 2h x 2w output
 *   to the original h x w input using a simple index mapping.
 * - Time Complexity: O(w * h) - we visit each cell once
 * - Space Complexity: O(w * h) - to store the input image
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

int main() {
  int w, h;
  scanf("%d %d\n", &w, &h);
  std::vector<std::string> s(h);
  for (int p = 0; p < h; p++) {
    getline(std::cin, s[p]);
  }
  // Loop to generate the 2w x 2h output image
  for (int p = 0; p < 2 * w; p++) {
    for (int q = 0; q < 2 * h; q++) {
      // Map each output pixel to the input pixel using integer division
      std::cout << s[q / 2][p / 2];
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/