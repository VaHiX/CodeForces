// Problem: CF 911 A - Nearest Minimums
// https://codeforces.com/contest/911/problem/A

/*
 * Problem: Nearest Minimums
 * 
 * Algorithm/Technique: Single Pass Linear Scan
 * 
 * Time Complexity: O(n) - We iterate through the array once.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 * 
 * Approach:
 * - Keep track of the minimum value seen so far and the index of the last occurrence of this minimum.
 * - When a new smaller value is found, update the minimum and reset the tracking.
 * - When the same minimum value is found again, calculate the distance from the previous occurrence
 *   and update the minimum distance if this is smaller.
 */

#include <cstdio>
int main() {
  int n, x, min, min2, p = 0;
  scanf("%d%d", &n, &min);  // Read size and first element
  min2 = n;  // Initialize min2 to a value larger than any possible distance
  for (int i = 1; i < n; i++) {
    scanf("%d", &x);  // Read next element
    if (x < min) {
      // Found a new smaller minimum
      min = x;
      min2 = n;  // Reset min2
      p = i;  // Update index of last minimum occurrence
    } else if (x == min) {
      // Found another occurrence of the minimum
      if (i - p < min2)  // If distance to previous is smaller than current min2
        min2 = i - p;
      p = i;  // Update index of last minimum occurrence
    }
  }
  printf("%d\n", min2);
  return 0;
}


// https://github.com/VaHiX/CodeForces/