// Problem: CF 1772 D - Absolute Sorting
// https://codeforces.com/contest/1772/problem/D

/*
 * Problem: D. Absolute Sorting
 * 
 * Purpose: Given an array of integers, determine a value x such that applying 
 *          absolute difference (a[i] - x) to all elements results in a sorted array.
 *          Return any valid x or -1 if impossible.
 * 
 * Algorithm/Technique:
 *   - For each adjacent pair (a[i], a[i+1]), derive constraints on x:
 *     - If a[i] <= a[i+1], then |a[i] - x| <= |a[i+1] - x| implies x must be in a certain range.
 *     - The derived constraints from all pairs are intersected using min/max updates.
 *   - If final valid range [mn, mx] is empty (mn > mx), return -1.
 * 
 * Time Complexity: O(n) per test case, O(n) overall with total n <= 2*10^5
 * Space Complexity: O(1)
 */

#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a > b) ? b : a; }

int sol() {
  int mn = 0, mx = 1e9 + 1; // Initialize valid range for x
  int a, b, n;
  scanf("%d", &n);
  n--; // We will process n-1 pairs
  scanf("%d", &a); // Read first element
  
  while (n--) { // Process remaining elements
    scanf("%d", &b);
    if (mn <= mx) { // Only process if valid range exists
      if (a > b) {
        // Constraint: |a - x| <= |b - x| when a > b
        // This implies x >= (a + b) / 2 + 0.5 (rounded up)
        // Use float for precise calculation
        mn = max(mn, (float)(a + b) / 2 + 0.6);
      } else if (a < b) {
        // Constraint: |a - x| <= |b - x| when a < b
        // This implies x <= (a + b) / 2
        mx = min(mx, (a + b) / 2);
      }
      a = b; // Update previous element
    }
  }
  
  // If range is invalid, return -1. Else return an x in the range
  return (mn > mx) ? -1 : (mx + mn) / 2;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", sol());
  }
}


// https://github.com/VaHiX/CodeForces/