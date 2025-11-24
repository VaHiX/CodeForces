// Problem: CF 643 A - Bear and Colors
// https://codeforces.com/contest/643/problem/A

/*
 * Problem: Bear and Colors
 * Algorithm: Brute force with frequency counting
 * Time Complexity: O(n^2 * n) = O(n^3) in worst case, but optimized to O(n^2) due to early termination
 * Space Complexity: O(n)
 *
 * The solution iterates through all possible intervals [left, right] and maintains a count of colors
 * in that interval. For each interval, it determines the dominant color and increments the answer
 * counter for that color.
 */

#include <cstdio>
#include <vector>
int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n, 0); // Array to store the colors of balls (0-indexed)
  for (int p = 0; p < n; p++) {
    scanf("%d", &a[p]);
    --a[p]; // Convert to 0-indexed color
  }
  std::vector<int> ans(n, 0); // Result array to store count of intervals for each color
  for (int left = 0; left < n; left++) {
    std::vector<int> count(n, 0); // Count frequency of each color in current interval
    int best(0), bestCount(0); // Track the dominant color and its count in current interval
    for (int right = left; right < n; right++) {
      int col = a[right];
      ++count[col]; // Increment count for the current color
      // Update dominant color if current color has higher count or equal count but smaller index
      if (count[col] > bestCount || (count[col] == bestCount && col < best)) {
        best = col;
        bestCount = count[col];
      }
      ++ans[best]; // Increment the count for the dominant color in this interval
    }
  }
  for (int p = 0; p < n; p++) {
    printf("%d ", ans[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/