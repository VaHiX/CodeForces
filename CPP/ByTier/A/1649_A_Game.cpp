// Problem: CF 1649 A - Game
// https://codeforces.com/contest/1649/problem/A

/*
Algorithm: Game
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves finding the minimum cost to traverse from the first to the last location,
where each location is either land (1) or water (0). You can move freely between adjacent
land locations, but can make one "free jump" of cost x from any land location i to another
land location i+x. The idea is to find the leftmost and rightmost land locations in the array,
and the minimum coins needed is the distance between them, but only if there's a gap that
requires a jump.

Key insight:
- Find the leftmost land (a[left] = 1) and rightmost land (a[right] = 1).
- The cost of jumping from left to right is (right - left) coins.
- The free moves between adjacent lands are already handled, so we only need to account
  for one jump that spans the gap.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long left(0); // Find the first land location
    while (left + 1 < n && a[left + 1]) { // Keep moving right while we see land
      ++left;
    }
    long right(n - 1); // Start from last index
    while (right > 0 && a[right - 1]) { // Keep moving left while we see land
      --right;
    }
    long cost = (right - left); // Calculate the jump distance
    cost = (cost > 0) ? cost : 0; // Ensure non-negative cost
    printf("%ld\n", cost);
  }
}


// https://github.com/VaHiX/codeForces/