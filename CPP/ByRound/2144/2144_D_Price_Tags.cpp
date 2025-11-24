// Problem: CF 2144 D - Price Tags
// https://codeforces.com/contest/2144/problem/D

/*
D. Price Tags

Purpose:
This code solves a problem where we need to determine the optimal coefficient 'x' (x > 1) to minimize the cost of repurposing existing price tags while maximizing revenue from a sale. 
Each item's price is rounded up to the nearest multiple of x, and new price tags are needed for items whose final price does not match any existing tag. The goal is to maximize total income = sum of new prices - cost of printing new tags.

Algorithms/Techniques:
- Frequency counting using a vector (cnt)
- Prefix sums for fast range queries (cnts)
- Brute-force enumeration over possible x values from 2 to 200000
- Efficient calculation of total income for each x

Time Complexity: O(200000 * n + 200000) = O(n + 200000) per test case (amortized)
Space Complexity: O(200001) = O(1) in terms of input size (fixed array sizes)

*/

#include <algorithm>
#include <iostream>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;
const int MOD = 998244353;

void solve() {
  int n, y;
  cin >> n >> y;
  vector<int> cnt(200001), cnts(200002); // cnt stores frequency of each price tag; cnts - prefix sum array
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    cnt[a]++; // Count occurrences of each original price
  }
  // Build prefix sums for efficient range queries
  for (int i = 1; i <= 200001; i++)
    cnts[i] = cnts[i - 1] + cnt[i - 1];
  
  ll res = -1e18; // Initialize result to very small value
  for (int x = 2; x <= 200000; x++) { // Iterate over all possible x values from 2 to 200000
    ll cres = 0; // Current total income for this x
    int col = 0; // Number of items we can reuse price tags for
    for (int v = 1;; v++) { // Loop through the buckets of size x
      int l = (v - 1) * x + 1, r = v * x + 1; // Define range [l, r) for current group
      if (l >= 200001)
        break;
      r = min(r, 200001); // Make sure range does not exceed maximum price
      col += min(cnt[v], cnts[r] - cnts[l]); // Count how many items with original value 'v' we can reuse tags from this bucket
      cres += 1LL * (cnts[r] - cnts[l]) * v; // Add contribution of these items to the total income
    }
    cres -= 1LL * (n - col) * y; // Subtract cost of printing new tags
    res = max(res, cres); // Update maximum income
  }
  cout << res << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cout.tie(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/