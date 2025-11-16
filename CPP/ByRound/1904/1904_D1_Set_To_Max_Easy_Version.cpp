// Problem: CF 1904 D1 - Set To Max (Easy Version)
// https://codeforces.com/contest/1904/problem/D1

/*
Algorithm: Monotonic Stack + Greedy + Set + Simulation
Time Complexity: O(n^2) in worst case due to nested operations and set lookups, but in practice much better due to early exits
Space Complexity: O(n) for storing stacks, arrays, and sets

This solution attempts to determine whether array 'a' can be transformed into array 'b' using the given operation:
- Choose a subarray [l,r] and set all elements in that subarray to the maximum value in that subarray.

The approach uses:
1. Monotonic stacks to compute for each element the left and right boundaries where it's the maximum.
2. For each unique value in the arrays, simulate how many elements from 'b' can be matched to 'a' under the constraints.
3. Uses a set to track already processed positions and a greedy approach to check if any unmatched elements remain.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <vector>

using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1), b(n + 1); // 1-indexed arrays
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    cin >> b[i];
  
  // l[i] = leftmost position where a[i] is maximum in the range
  // r[i] = rightmost position where a[i] is maximum in the range
  vector<int> l(n + 1), r(n + 1, n + 1);
  stack<int> s;
  
  // Compute right boundaries using monotonic stack
  for (int i = 1; i <= n; i++) {
    while (s.size() && a[i] > a[s.top()]) {
      r[s.top()] = i;   // Mark the right boundary for previous elements
      s.pop();
    }
    s.push(i);
  }
  
  // Clear stack
  while (s.size())
    s.pop();
  
  // Compute left boundaries using monotonic stack (reverse direction)
  for (int i = n; i >= 1; i--) {
    while (s.size() && a[i] > a[s.top()]) {
      l[s.top()] = i;   // Mark the left boundary for previous elements
      s.pop();
    }
    s.push(i);
  }
  
  // Group indices by their values in both arrays
  vector<vector<int>> pa(n + 1), pb(n + 1);
  for (int i = 1; i <= n; i++) {
    pa[a[i]].push_back(i);
    pb[b[i]].push_back(i);
  }
  
  // Set to track already processed positions
  set<int> done;
  done.insert(0);
  done.insert(n + 1);
  
  // Process each unique value
  for (int x = 1; x <= n; x++) {
    // Reverse pb[x] to process from right to left (greedy match)
    reverse(all(pb[x]));
    vector<int> save = pb[x];  // Save for restoration
    
    for (int i : pa[x]) {
      // Get the valid range [L, R] for the element i under current constraints
      int L = l[i], R = r[i];
      L = max(L, *prev(done.upper_bound(i))); // Find left boundary based on already processed
      R = min(R, *done.lower_bound(i));       // Find right boundary based on already processed
      
      // Remove elements from pb[x] that fall inside [L, R]
      while (pb[x].size() && pb[x].back() > L && pb[x].back() < R)
        pb[x].pop_back();
    }
    
    // Mark positions in pb[x] as processed
    for (int i : save)
      done.insert(i);
    
    // If there are remaining indices in pb[x], impossible to make a match
    if (pb[x].size()) {
      cout << "NO" << '\n';
      return;
    }
  }
  
  cout << "YES" << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/