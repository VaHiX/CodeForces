// Problem: CF 1788 E - Sum Over Zero
// https://codeforces.com/contest/1788/problem/E

/*
Purpose: 
This code solves the problem of finding the maximum sum of lengths of non-overlapping segments 
in an array such that the sum of elements in each segment is non-negative. It uses a combination 
of prefix sums, coordinate compression, and a Fenwick Tree (Binary Indexed Tree) for efficient 
queries and updates.

Algorithms/Techniques:
- Prefix Sum: To quickly calculate subarray sums.
- Coordinate Compression: To map prefix sums to indices for efficient Fenwick Tree usage.
- Fenwick Tree (Binary Indexed Tree): Used for range maximum queries and updates in O(log n) time.
- Dynamic Programming: To track the maximum possible sum of segment lengths up to each index.

Time Complexity: O(n log n)
Space Complexity: O(n)

The algorithm works by scanning the array and using the Fenwick Tree to efficiently maintain 
the best possible sum of segment lengths ending at previous positions, ensuring no overlaps.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int max_n = 500005, inf = 10000000;
int t, n, a[max_n], dp[max_n], ord[max_n], fen[max_n];
long long pref[max_n];

// Returns the least significant bit of a
int lsb(int a) { return (a & -a); }

// Updates Fenwick Tree at position 'pos' with value 'val'
void add(int pos, int val) {
  while (pos <= n) {
    fen[pos] = max(fen[pos], val);
    pos += lsb(pos);
  }
}

// Queries Fenwick Tree for maximum value up to position 'pos'
int ask(int pos) {
  int val = -inf;
  while (pos) {
    val = max(fen[pos], val);
    pos -= lsb(pos);
  }
  return val;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  t = 1;
  while (t--) {
    cin >> n;
    vector<pair<long long, int>> v;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      pref[i] = pref[i - 1] + a[i];  // Compute prefix sums
      v.push_back({pref[i], i});     // Store prefix sum and its index
    }
    sort(v.begin(), v.end());        // Sort by prefix sum
    for (int i = 0; i < n; i++) {
      ord[v[i].second] = i + 1;      // Coordinate compression: map index to compressed rank
    }
    for (int i = 1; i <= n; i++) {
      fen[i] = -inf;                 // Initialize Fenwick Tree
    }
    for (int i = 1; i <= n; i++) {
      // dp[i] tracks maximum f(S) considering subarray [1, i]
      dp[i] = (dp[i - 1] + (a[i] >= 0));  // Default case: extend last segment or start new one
      dp[i] = max(dp[i], ask(ord[i]) + i); // Check optimal previous segment using Fenwick Tree
      if (pref[i] >= 0)                    // If prefix sum is non-negative, we can start a new segment
        dp[i] = i;
      add(ord[i], dp[i] - i);             // Update Fenwick Tree with current dp[i] - i
    }
    cout << dp[n] << "\n";                // Output result for the full array
    for (int i = 0; i <= n; i++) {
      a[i] = 0, dp[i] = 0, ord[i] = 0, fen[i] = 0, pref[i] = 0;  // Reset arrays for next test case
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/