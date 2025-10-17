// Problem: CF 2128 E2 - Submedians (Hard Version)
// https://codeforces.com/contest/2128/problem/E2

/* 
 * E2. Submedians (Hard Version)
 * 
 * Purpose: Find all possible submedians of an array, where a submedian is a value that can be the median of some subarray of length at least k.
 *
 * Algorithms/Techniques:
 * - Binary search on the answer to find the range of valid submedians
 * - Sliding window technique to efficiently check if a given value is a submedian
 * - Transformation trick using reverse mapping for efficient computation
 * 
 * Time Complexity: O(n log n) per test case due to binary search and linear scan.
 * Space Complexity: O(n) for auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
using namespace std;
const int N = 3e5 + 5;
int T, n, k, a[N], s[N], c[N], mn, mx, now;

// Check if value x is a valid submedian
bool Check(int x, int &ansl, int &ansr) {
  for (int i = 1; i <= n; ++i) {
    s[i] = s[i - 1] + (a[i] >= x ? 1 : -1); // Compute prefix sum using binary values
  }
  for (int i = k, mn = n + 1, l = 0; i <= n; ++i) {
    if (s[i - k] < mn) { // Track minimum from previous window
      mn = s[i - k], l = i - k;
    }
    if (s[i] >= mn) { // If current prefix is larger or equal, we found a valid subarray
      ansl = l + 1, ansr = i;
      return 1;
    }
  }
  return 0;
}

// Binary search on the range of possible submedians
void Binary(int &ans, int &ansl, int &ansr) {
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1; // Midpoint computation using bit shift
    if (Check(mid, ansl, ansr)) {
      l = mid + 1; // Try for larger values
    } else {
      r = mid - 1; // Try for smaller values
    }
  }
  Check(r, ansl, ansr), ans = r;
}

// Add or remove element from window and update current counter
void Add(int x, int v) { 
  c[x] += v; 
  now += x >= mn ? v : -v; 
}

void Solve() {
  fill_n(c + 1, n, 0), now = 0; // Reset auxiliary arrays and counters
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int l1, r1, l2, r2;
  
  Binary(mx, l2, r2); // Find maximum valid submedian
  
  for (int i = 1; i <= n; ++i) {
    a[i] = n - a[i] + 1; // Transform array to invert values
  }
  
  Binary(mn, l1, r1), mn = n - mn + 1; // Find minimum valid submedian after transformation
  
  for (int i = 1; i <= n; ++i) {
    a[i] = n - a[i] + 1; // Revert back to original values
  }
  
  // Build the range of possible submedians from l1,r1 to l2,r2
  for (int i = l1; i <= r1; ++i) {
    ++c[a[i]], now += a[i] >= mn ? 1 : -1;
  }

  cout << mx - mn + 1 << '\n';

  while (mn <= mx) {
    while (now >= 0) { // While we have valid counters, output submedians in increasing order
      cout << mn << ' ' << l1 << ' ' << r1 << '\n';
      now -= c[mn++] << 1; // Adjust counter by doubling the count for current value
    }

    // Move pointers based on which window has more elements to expand
    if (l1 > l2) {
      Add(a[--l1], 1); // Expand left side of first window
    } else if (r1 < r2) {
      Add(a[++r1], 1); // Expand right side of first window
    } else if (l1 < l2) {
      Add(a[l1++], -1); // Shrink left side of first window
    } else if (r1 > r2) {
      Add(a[r1--], -1); // Shrink right side of first window
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/