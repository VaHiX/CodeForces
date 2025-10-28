// Problem: CF 2085 F2 - Serval and Colorful Array (Hard Version)
// https://codeforces.com/contest/2085/problem/F2

/*
F2. Serval and Colorful Array (Hard Version)
Algorithms/Techniques: Sliding window, difference array, prefix sum, greedy
Time Complexity: O(n)
Space Complexity: O(n)

This problem asks for the minimum number of adjacent swaps to make at least one subarray of length k colorful.
A colorful subarray is a permutation of integers from 1 to k.

The approach uses:
- Preprocessing positions of elements
- Difference array technique to efficiently compute cost changes
- Prefix sum to maintain current cost
- Greedy optimization with sliding window
*/

#include <algorithm>
#include <bits/std_abs.h>
#include <iostream>
using namespace std;
#define int long long
#define N 1000100
int t, n, k, val[N], pre[N], del[N];

int work() {
  // Initialize arrays
  for (int i = 1; i <= n; ++i)
    pre[i] = del[i] = 0;
  
  int sum = 0;
  // Process each element from left to right
  for (int i = 1; i <= n; ++i) {
    // If this value hasn't appeared before, add cost of placing it
    if (pre[val[i]] == 0)
      sum += i - 1;
    else {
      // If previously seen, remove contribution from previous position
      // Del[median]-- and Del[median+1]--; 
      // This accounts for removing elements from window that contain this value
      del[(pre[val[i]] + i) / 2]--, del[(pre[val[i]] + i + 1) / 2]--;
    }
    
    // Add cost of current position to difference array
    del[i] += 2;
    pre[val[i]] = i; // Update last seen index
  }
  
  int ans = 1e18, dis = -k;
  // Compute minimum cost over all possible windows
  for (int i = 1; i <= n; ++i) {
    ans = min(ans, sum); // Keep track of minimal sum
    dis += del[i];       // Update difference
    sum += dis;          // Propagate changes to cumulative sum
  }
  
  // Adjust for optimal subarray cost
  for (int i = 1; i <= k; ++i)
    ans -= abs((k + 1) / 2 - i);
    
  return ans;
}

signed main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
      cin >> val[i];
    cout << work() << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/