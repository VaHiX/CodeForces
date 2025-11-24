// Problem: CF 2172 C - Circles Are Far from Each Other
// https://codeforces.com/contest/2172/problem/C

/*
Purpose:
This program solves a problem where we need to arrange n circles on a 2D plane such that:
1. All centers are collinear
2. Distance between any two centers is at most k
3. No two circles intersect
4. If a circle encloses two others, one must enclose the other (transitivity)
5. First l circles may or may not be enclosed, remaining n-l must be enclosed
The goal is to maximize the minimum distance between any two points from different circles (quality of arrangement).

Algorithms/Techniques:
- Greedy approach with multiset for maintaining circle radii
- Binary search on answer or direct calculation based on constraints
- Handling of different cases for enclosures and distances

Time Complexity: O(n log n) due to sorting and multiset operations
Space Complexity: O(n) for storing radii and multiset storage
*/

#include <limits.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
#define int long long

void solve() {
  int n, l, k;
  cin >> k >> n >> l;
  vector<int> r(n);
  for (int i = 0; i < n; i++)
    cin >> r[i];
  k = k - r[0]; // Adjust k for the first circle's radius
  multiset<int, greater<int>> a; // Multiset to store radii, sorted in descending order
  a.insert(r[0]); // Insert first circle's radius
  int ng = 0, ans = INT_MAX; // ng counts how many circles are enclosed, ans tracks minimum distance
  
  // Skip over duplicate radii at the beginning for l
  while (l > 0 && r[l] == r[l - 1]) {
    l++;
  }
  
  // Process first l circles (may or may not be enclosed)
  for (int i = 1; i < l; i++) {
    if (ng == 0) {
      // If no circle is enclosed yet, check which one is better to enclose
      if (k - r[i] > *(a.begin()) - r[i]) {
        // Enclose this circle and update k and ng
        ng++;
        k = k - r[i];
        a.insert(r[i]);
      } else {
        // Check if we can replace the largest enclosed circle with this one
        int x = *a.begin();
        a.erase(a.begin());
        a.insert(r[i]);
        ans = min(ans, x - r[i]); // Update the minimum gap
      }
      continue;
    }
    
    // If at least one circle is already enclosed, determine if we can include another
    if (k - 2 * r[i] > (*(a.begin()) - r[i]) * (ng + 1)) {
      // We can enclose this circle
      ng++;
      k = k - 2 * r[i]; // Decrease k by twice the radius (center to center distance)
      a.insert(r[i]);
    } else {
      // Replace the largest circle with current circle if beneficial
      int x = *a.begin();
      a.erase(a.begin());
      a.insert(r[i]);
      ans = min(ans, x - r[i]); // Update minimum gap
    }
  }
  
  // For the remaining circles that must be enclosed
  for (int i = l; i < n; i++) {
    ans = min(ans, *(a.begin()) - r[i]); // Minimum gap between top circle and current circle
    a.insert(r[i]);
    a.erase(a.begin()); // Remove the largest circle and insert current
  }
  
  // Final check: compare calculated answer vs k/ng for optimal spacing
  if (ng == 0 || (double)k / ng > (double)ans)
    cout << ans;
  else {
    if (ng > 0 && k % ng == 0)
      cout << k / ng; // Integer division case
    else
      cout << k << '/' << ng; // Fractional case with reduced form
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}


// https://github.com/VaHiX/CodeForces/