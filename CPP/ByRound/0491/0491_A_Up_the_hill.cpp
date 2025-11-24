// Problem: CF 491 A - Up the hill
// https://codeforces.com/contest/491/problem/A

/*
 * Code Purpose: 
 *   This program reconstructs a possible sequence of stop heights for a hiking expedition based on the number of days spent climbing up and down hills.
 *   The key insight is to arrange the heights such that:
 *     - The first `up` steps are strictly increasing (climbing up).
 *     - The remaining steps are decreasing (descending).
 *     - All heights are distinct integers from 1 to N.
 * 
 * Algorithm:
 *   1. Initialize a sequence of heights from 1 to N.
 *   2. Reverse the suffix starting from index `up` to make the last part
 *      of the sequence decreasing.
 * 
 * Time Complexity: O(N)
 *   - Initialization of the vector takes O(N).
 *   - Reversing the suffix takes O(N - up) = O(N).
 *   - Printing the result takes O(N).
 * 
 * Space Complexity: O(N)
 *   - A vector of size N is used to store the heights.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long up, down;
  scanf("%ld\n%ld", &up, &down);
  long N = up + down + 1;
  std::vector<long> height(N);
  for (int p = 0; p < N; p++) {
    height[p] = p + 1;  // Fill the vector with values 1, 2, ..., N
  }
  std::reverse(height.begin() + up, height.end());  // Reverse the part after the climbing phase to make it descending
  for (int p = 0; p < N; p++) {
    printf("%ld ", height[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/