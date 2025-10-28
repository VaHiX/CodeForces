// Problem: CF 1870 E - Another MEX Problem
// https://codeforces.com/contest/1870/problem/E

/*
Algorithm: Dynamic Programming with Bitwise XOR Optimization
Time Complexity: O(n^2) per test case, where n is the size of the array.
Space Complexity: O(n^2) due to the storage of intermediate XOR values and auxiliary arrays.

This solution uses a dynamic approach to track the maximum possible XOR of MEX values
for all possible non-overlapping subarray selections. For each element in the array,
it updates the set of possible XORs based on the MEX values computed from prefixes
and ensures that overlapping subarrays are handled properly.
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long
#define MOD 998244353
#define endl "\n"
#define N 5050
vector<int> a;
int n;
int mex_r[N]; // Stores the rightmost position where MEX value was updated
vector<int> new_xor[N]; // Stores possible XOR values at each position
int val_r[N]; // Stores the latest index of each value
bool over[N + N]; // Marks which XOR values are achievable

int solve(int testcase) {
  cin >> n;
  // Initialize arrays
  for (int i = 0; i <= n; i++)
    mex_r[i] = 0, val_r[i] = -1, new_xor[i].clear();
  for (int i = 2 * n; i >= 0; i--)
    over[i] = false;
  
  new_xor[0].push_back(0); // Base case: XOR of empty set is 0
  over[0] = true;

  for (int i = 1; i <= n; i++) {
    int val;
    cin >> val;
    val_r[val] = i; // Record the index of the value
    int cur = i; // Current boundary for subarrays
    for (int mex = 1; mex <= n; mex++) {
      cur = min(cur, val_r[mex - 1]); // Update the left boundary for MEX mex
      if (cur < 0) break; // No more valid subarrays
      if (val_r[mex] >= cur) continue; // Value mex already included in current range
      if (mex_r[mex] < cur) { // If this MEX hasn't been processed for range [mex_r[mex], cur)
        int l = mex_r[mex];
        // Propagate existing XORs into new XORs with mex
        for (int pos = l; pos < cur; pos++) {
          for (auto x : new_xor[pos]) {
            int to = x ^ mex; // Compute new XOR by combining with mex
            if (!over[to]) {
              over[to] = true;
              new_xor[i].push_back(to); // Add to possible XORs
            }
          }
        }
        mex_r[mex] = cur; // Update the boundary for MEX mex
      }
    }
  }
  // Return the maximum possible XOR value
  for (int i = 2 * n; i >= 0; i--)
    if (over[i]) {
      cout << i << endl;
      return 0;
    }
  return 0;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int totalcases = 1;
  cin >> totalcases;
  for (int testcase = 1; testcase <= totalcases; testcase++)
    solve(testcase);
  return 0;
}


// https://github.com/VaHiX/CodeForces/