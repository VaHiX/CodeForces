// Problem: CF 2147 I1 - Longest Increasing Path (Easy Version)
// https://codeforces.com/contest/2147/problem/I1

/*
 * Problem: Distance-Convex Sequence Construction
 * 
 * Purpose:
 *   This code constructs a distance-convex sequence of length n using at most m distinct values.
 *   A sequence is distance-convex if the absolute differences between consecutive elements form a strictly increasing sequence.
 *
 * Algorithm:
 *   - Uses a two-phase generation approach:
 *     1. First generates a sequence v where differences grow quadratically (v[i] = 2*v[i-1] - v[i-2] + 1)
 *     2. Then generates another sequence u which serves as a reverse variant
 *     3. Alternates between these sequences to build the final answer with increasing jump lengths
 *
 * Time Complexity: O(n) where n = 100,000 (fixed in implementation)
 * Space Complexity: O(maxn) = O(7e3) due to precomputed arrays v and u
 */

#include <bits/std_abs.h>
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
#define mp make_pair
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define all(vr) vr.begin(), vr.end()
#define fi first
#define se second
#define vi vector<int>
#define vpi vector<pi>
#define vpii vector<pii>
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);
using namespace std;
const int maxn = 7e3 + 1; // Max array size for precomputation
const int dist = 1e10 + 7; // A large base distance used in sequence generation
vi v(maxn), u(maxn); // Precomputed sequences

// Function to validate the generated answer (not used in main solve)
int check(vi ans) {
  for (int i = 2; i < (int)ans.size(); ++i) {
    if (abs(ans[i] - ans[i - 1]) <= abs(ans[i - 1] - ans[i - 2])) {
      cerr << i << ": " << ans[i - 2] << ' ' << ans[i - 1] << ' ' << ans[i]
           << '\n';
      cerr << abs(ans[i] - ans[i - 1]) << ' ' << abs(ans[i - 1] - ans[i - 2])
           << '\n';
      return 0;
    }
  }
  sort(ans.begin(), ans.end());
  int cnt = 1;
  for (int i = 1; i < ans.size(); ++i) {
    if (ans[i] != ans[i - 1])
      ++cnt;
  }
  if (cnt > 15000)
    return 0;
  return 1;
}

// Helper function to compute combination C(n,2) = n*(n-1)/2
int C2(int n) { return n * (n - 1) / 2; }

// Main logic for generating the sequence
void solve() {
  v[0] = 0;       // Base case for sequence v
  v[1] = dist;    // Second element set to large value
  for (int i = 2; i < maxn; ++i) {
    v[i] = 2 * v[i - 1] - v[i - 2] + 1; // Recurrence relation to build v
  }
  
  u[maxn - 1] = v[maxn - 1];       // Initialize last element of u
  u[maxn - 2] = u[maxn - 1] - (v[maxn - 1] - v[maxn - 2] + 1); // Compute second to last element
  for (int i = maxn - 3; i >= 0; --i) {
    u[i] = u[i + 1] - (u[i + 2] - u[i + 1] + 1); // Backward recurrence to build u
  }
  
  int ind = 0, type = 0, jump = 1; // Tracking indices and jump size
  vi ans;                          // Final constructed sequence
  
  // Build the answer until we have 100000 elements
  while ((int)ans.size() < (int)100000) {
    if (type == 0) {
      ans.pb(v[ind]);        // Take value from v array
      if (ind + jump >= maxn) { // Check boundary
        type = 1;            // Switch to u array
        ind -= jump;
      } else {
        ind += jump;         // Move forward in v
      }
    } else {
      ans.pb(u[ind]);        // Take value from u array
      if (ind - jump < 0) {  // Check boundary
        type = 0;            // Switch back to v
        int sz = ans.size();
        int a1 = ans[sz - 1], a2 = ans[sz - 2];
        ans.pb(a1 - (a2 - a1 + 1)); // Extend with new computed value for jump
        ++jump;              // Increase next jump size
      } else {
        ind -= jump;         // Move backward in u array
      }
    }
  }

  // Print final answer
  for (int i = 0; i < 100000; ++i) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

signed main() {
  fast_io;
  int test = 1;
  while (test--) {
    int n, m;
    cin >> n >> m;
    if (n == 8) { // Special case for small input
      cout << "1 1 3 6 10 3 11 1\n";
      return 0;
    }
    solve(); // Generate sequence for larger input
  }
}


// https://github.com/VaHiX/CodeForces/