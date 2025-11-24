// Problem: CF 2003 D1 - Turtle and a MEX Problem (Easy Version)
// https://codeforces.com/contest/2003/problem/D1

/*
D1. Turtle and a MEX Problem (Easy Version)
Algorithms/Techniques: 
  - Brute Force with Optimization using Set/MEX Logic
  - Greedy approach to find maximum mex reachable from a starting value
  - Preprocessing sequences to calculate maximum mex possible

Time Complexity: O(N * L + M) where N is number of sequences, L is average length of sequences
Space Complexity: O(max_value) ~ O(10^9) but optimized with a fixed size array of size ~2e5
*/

#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5; // Max size for visited array, large enough to fit any valid input constraints
int n, a[N + 10], l, t, m, mx; // Global variables for input and computation
bool vis[N + 10]; // Visited array to mark presence of numbers in current sequence

void solve() {
  cin >> n >> m, mx = 0;
  bool op;
  for (int i = 1; i <= n; ++i) {
    cin >> l; // Length of current sequence
    for (int j = 1; j <= l; ++j)
      cin >> a[j], vis[min(a[j], N)] = true; // Mark presence of elements in array up to index N
    
    op = false;
    for (int j = 0;; ++j) {
      if (!vis[j] && op) { // If we found a gap after previously encountering non-missing element
        mx = max(mx, j); // Update the maximum mex possible with current sequence
        break;
      }
      if (!vis[j])
        op = true; // Mark that we've seen some elements before this position
    }
    
    for (int j = 1; j <= l; ++j)
      vis[min(a[j], N)] = false; // Reset visited array for next iteration to avoid interference
  }
  
  if (m <= mx) // If m is smaller or equal to max mex, all values from 0 to m contribute directly
    cout << mx * 1LL * m + mx << "\n";
  else // Otherwise some values exceed mx and contribute as arithmetic sequence
    cout << mx * 1LL * mx + (mx + 1 + m) * 1LL * (m - mx) / 2 + mx << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/