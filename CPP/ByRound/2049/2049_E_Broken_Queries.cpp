// Problem: CF 2049 E - Broken Queries
// https://codeforces.com/contest/2049/problem/E

/*
 * Problem: E. Broken Queries
 * Purpose: Determine the hidden integer k in a binary array using at most 33 queries.
 *          The array has exactly one 1, and a device returns inverted results for ranges
 *          of length >= k.
 * 
 * Algorithm:
 *   - Use binary search techniques to deduce k.
 *   - First, identify which half of the array contains the 1 by querying a mid-range.
 *   - Then, further partition the array and use the device's behavior to narrow down k.
 *   - The key insight is that queries of size >= k return inverted answers.
 * 
 * Time Complexity: O(log n) per test case due to binary search
 * Space Complexity: O(1) - only using a few variables
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int n;

// Function to send query to device
void print(int x, int y) {
  printf("? %d %d\n", x, y);
  fflush(stdout);
}

// Binary search function to find k based on the results
int work(int l, int r, bool b, int c) {
  int mid;
  while (l <= r) {
    mid = (l + r) >> 1;  // Midpoint calculation using bit shift
    if (b) {
      print(1, mid);     // Query the left side
    } else {
      print(n - mid + 1, n); // Query the right side
    }
    int x;
    scanf("%d", &x);
    if (x == c) {
      l = mid + 1;       // Adjust search space
    } else {
      r = mid - 1;       // Adjust search space
    }
  }
  return l;
}

// Main solving logic for one test case
void solve() {
  scanf("%d", &n);
  int l, r, mid;
  mid = n >> 1;          // Midpoint of array
  print(1, mid);         // Query first half
  int x;
  scanf("%d", &x);
  if (x) {               // If result is 1, 1 is in left half
    l = 1, r = mid;
  } else {               // Else, 1 is in right half
    l = mid + 1, r = n;
  }
  mid = (l + r) >> 1;    // Recalculate midpoint
  int xl, xr;
  print(l, mid);         // Query left partition of current segment
  scanf("%d", &xl);
  print(mid + 1, r);     // Query right partition of current segment
  scanf("%d", &xr);
  int ans;
  if (xl == xr) {        // If both partitions have same result
    if (xl) {            // Both are 1
      ans = work(2, n >> 2, (l == 1), 0);  // Special handling for 1s
    } else {             // Both are 0
      ans = work((n >> 2) + 1, n >> 1, (l == 1), 0);  // Special handling for 0s
    }
  } else {               // If partitions are different
    ans = work((n >> 1) + 1, n - 1, (l == 1), 1);  // Regular binary search
  }
  printf("! %d\n", ans);
  fflush(stdout);
}

// Main loop processing multiple test cases
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/