// Problem: CF 1120 A - Diana and Liana
// https://codeforces.com/contest/1120/problem/A

/*
 * Problem: Diana and Liana
 * 
 * Purpose:
 * This code determines if it's possible to remove some flowers from a liana such that:
 * 1. At least n workpieces can be created (each of k flowers)
 * 2. At least one workpiece conforms to Diana's flower schematic
 * 
 * Algorithm:
 * - Sliding window technique to find valid subarrays of size up to n+k that contain enough flowers
 * - Uses a frequency map to track required flowers in Diana's schematic
 * - Finds the first valid substring matching requirements using two pointers
 * 
 * Time Complexity: O(m)
 * Space Complexity: O(MAXA) = O(5e6)
 */

#include <stdio.h>
#include <stdlib.h>
#include <iosfwd>

using namespace std;
const int MAXA = 5e6;
int m, n, k, s, x, l, r, si[MAXA], bo[MAXA], siz[MAXA], a[MAXA], tot;
int check(int l, int r) {
  // Adjust left boundary to be divisible by k
  l -= (l - 1) % k;
  // Early exit if window too large
  if (r - l + 1 > n + k)
    return 0;
  int ans = r - l + 1 - k;
  if (ans < 0)
    ans = 0;
  printf("%d\n", ans);
  for (int i = l; i <= r; i++) {
    if (ans == 0)
      break;
    if (si[a[i]] > 0)
      si[a[i]]--; // If this flower is needed, use it up
    else
      ans--, printf("%d ", i); // Otherwise, remove this flower
  }
  exit(0);
}
int main() {
  scanf("%d%d%d%d", &m, &k, &n, &s);
  n = m - n * k; // Adjust n for remaining length after n*k workpieces
  for (int i = 1; i <= m; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= s; i++) {
    scanf("%d", &x);
    bo[x] = 1; // Mark which flowers are needed for Diana
    siz[x]++;  // Count required flowers
    si[x]++;   // Copy count for processing
    tot++;     // Total required flowers
  }
  r = 0;
  l = 0;
  // Extend right pointer to find valid window with enough flowers
  while (r <= m && tot > 0) {
    r++;
    if (bo[a[r]]) { // If current flower is needed
      siz[a[r]]--;  // Decrement count
      if (siz[a[r]] >= 0) // If still required
        tot--;            // Reduce total count
    }
  }
  // Move left pointer until we reach a required flower that's now overused
  while (l <= m) {
    l++;
    if (bo[a[l]]) {
      if (siz[a[l]] == 0)
        break;
      siz[a[l]]++; // Increase count as we move past this flower
    }
  }
  // If valid window found, check it
  if (l <= m && r <= m)
    check(l, r);
  // Slide window to find another valid substring
  while (r < m && l < m) {
    r++;
    // Find matching flower to continue sliding window
    while (a[r] != a[l] && r <= m) {
      if (bo[a[r]])
        siz[a[r]]--; // Decrease count if needed
      r++;
    }
    l++;
    // Move left pointer until we find valid position
    while ((!(bo[a[l]] && siz[a[l]] == 0) && l <= m)) {
      if (bo[a[l]])
        siz[a[l]]++; // Increase count if needed
      l++;
    }
    if (l > m || r > m)
      break;
    check(l, r);
  }
  printf("-1"); // No valid solution found
}


// https://github.com/VaHiX/codeForces/