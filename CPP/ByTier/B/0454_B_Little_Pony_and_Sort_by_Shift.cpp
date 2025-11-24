// Problem: CF 454 B - Little Pony and Sort by Shift
// https://codeforces.com/contest/454/problem/B

/*
 * Problem: Little Pony and Sort by Shift
 * Algorithm: Find the minimum number of right shifts (moving last element to front) to sort the array.
 * Approach:
 *   - Traverse the array and count how many times a number is greater than the next one.
 *   - If there's more than one such "down" point, sorting is impossible.
 *   - If there's exactly one "down" point, the minimum shifts = n - position_of_down.
 *   - Check if the array can be sorted by shifting: the last element must be <= first element.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> array(n, 0);
  for (int p = 0; p < n; p++) {
    scanf("%ld ", &array[p]);
  }
  bool down = 0, possible = 1;  // 'down' tracks if we've seen a decrease, 'possible' tracks if sorting is feasible
  long moves(0);
  for (int p = 1; p < n; p++) {
    if (array[p - 1] <= array[p]) {
      continue;  // Continue if sequence is non-decreasing
    }
    if (down) {
      possible = 0;  // If we've already seen a decrease, it's impossible to sort
      break;
    }
    down = 1;  // Mark that we've seen a decrease
    moves = n - p;  // Calculate moves needed from this point
    if (array[p] > array[0]) {
      possible = 0;  // If the element that breaks sequence is greater than first, impossible
      break;
    }
  }
  if (down && array[n - 1] > array[0]) {
    possible = 0;  // If the last element is greater than the first, impossible
  }
  if (!possible) {
    puts("-1");  // Print -1 if not possible
  } else {
    printf("%ld\n", moves);  // Otherwise, print the minimum moves
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/