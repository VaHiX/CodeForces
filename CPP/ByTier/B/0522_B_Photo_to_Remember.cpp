// Problem: CF 522 B - Photo to Remember
// https://codeforces.com/contest/522/problem/B

/*
Purpose: 
  This program calculates the minimum pixel area of a group photo taken at a party,
  where each photo excludes one person who acts as the photographer. 
  For each photo, we compute the minimum area that can accommodate all remaining friends,
  based on the sum of their widths and the maximum height among them.

Algorithms/Techniques:
  - Single pass to compute total width and find max height with second max height.
  - For each friend excluded, compute the area as (total_width - excluded_width) * max_height,
    with special handling if the excluded friend was the one with the maximum height.

Time Complexity: O(n)
Space Complexity: O(n)
*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> dim(n); // Store widths of friends
  long totalWidth(0), maxHeight(0), secondHeight(0), tallest(0); // Track max, second max heights and index of tallest
  for (long p = 0; p < n; p++) {
    long w, h;
    scanf("%ld %ld\n", &w, &h);
    dim[p] = w; // Store width for later use
    totalWidth += w; // Add to total width
    if (h >= maxHeight) { // If current height is greater than or equal to max
      secondHeight = maxHeight; // Update second max to previous max
      maxHeight = h; // Update max height
      tallest = p; // Record index of tallest person
    } else if (h >= secondHeight) { // Else, if it's second tallest
      secondHeight = h; // Update second max height
    }
  }
  for (long p = 0; p < n; p++) {
    // For each person excluded, compute area:
    // (total width minus excluded width) * (height of remaining max, or second max if excluded was max)
    printf("%ld ",
           (totalWidth - dim[p]) * (p == tallest ? secondHeight : maxHeight));
  }
  puts(""); // Print new line at end
  return 0;
}


// https://github.com/VaHiX/CodeForces/