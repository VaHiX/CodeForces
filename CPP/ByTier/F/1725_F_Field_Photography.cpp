// Problem: CF 1725 F - Field Photography
// https://codeforces.com/contest/1725/problem/F

/*
Code Purpose:
This program solves a problem where contestants from different provinces are positioned in a grid and can be moved left or right in rows. The goal is to determine the maximum number of contestants that can be aligned in a single column after performing operations such that the final value of Z (a bitwise OR of move distances) equals a given target W.

The algorithm uses the idea that for each bit position in W, we decide whether to include that bit in the set of operations (by checking if the bit is set in the final Z), and then compute for each possible power-of-2 value of W (up to 30 bits), how many contestants can be maximized in a column under the constraint that the total Z equals exactly W.

Algorithms/Techniques:
1. Bit manipulation to process each bit of the target value W.
2. For each power of 2 (1, 2, 4, ..., 2^30), precompute the maximum number of contestants that can be aligned in one column when Z equals that power of 2.
3. Use a sweep-line technique with events (start/end of intervals in a column) to count maximum overlap.
4. Preprocessing of intervals to find overlap in column positions.

Time Complexity: O(N * log(max_W) + Q * log(max_W))
Space Complexity: O(N + Q)

*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define M 998244353
int i, j, k, n, m, t, l[100005], r[100005], f[66];

// Function to calculate maximum contestants in one column for a specific W value
int fuck(int w) {
  int i, j, k, res = 0, cur, x, y, res2 = 0;
  vector<pair<int, int>> v;  // Stores events for sweep line algorithm (position, delta)
  
  // Process each province
  for (i = 1; i <= n; i++) {
    // If entire range fit in w, it's already valid (doesn't contribute to overlap)
    if ((r[i] - l[i] + 1) >= w) {
      res++;  // Count one valid contestant (full overlap)
      continue;
    }
    x = l[i] % w;  // Start position mod w
    y = r[i] % w;  // End position mod w
    
    // Create events for interval [x, y]
    if (x <= y) {
      v.push_back({x, 1});     // Start of interval
      v.push_back({y + 1, -1}); // End of interval
    } else {
      // Handle wrap-around case
      swap(x, y);
      v.push_back({0, 1});          // Wrap start
      v.push_back({x + 1, -1});     // Wrap end
      v.push_back({y, 1});          // Real start after wrap
    }
  }
  
  // Sort all events by position
  sort(v.begin(), v.end());
  
  // Sweep line to find maximum overlap
  cur = 0;
  for (auto [i, j] : v) {
    cur += j;
    res2 = max(res2, cur);
  }
  
  return res + res2;  // Total = fixed contestants + maximum overlap
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> l[i] >> r[i];
    l[i]--;  // Convert to 0-based indexing
    r[i]--;
  }
  
  k = 1;
  // Precompute answers for powers of 2 (up to 2^30)
  for (t = 1; t <= 30; t++) {
    f[t] = fuck(k);
    k *= 2;
  }
  
  cin >> t;
  // Process each query
  while (t--) {
    cin >> n;
    j = 1;
    // Find the least significant bit that is set
    while (!(n & 1)) {
      j++;
      n /= 2;
    }
    cout << f[j] << '\n';  // Output precomputed result for that bit position
  }
}


// https://github.com/VaHiX/CodeForces/