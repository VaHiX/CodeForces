// Problem: CF 2160 G1 - Inverse Minimum Partition (Easy Version)
// https://codeforces.com/contest/2160/problem/G1

/*
G1. Inverse Minimum Partition (Easy Version)
Algorithms/Techniques: Dynamic Programming with Binary Search, Monotonic Stack
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

This problem involves finding the minimum cost to partition a sequence into subarrays,
where the cost of each subarray is defined as the ceiling of its length divided by its minimum element.
The solution uses dynamic programming with preprocessing to optimize the search for valid partitions.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define nl '\n'
const ll INF_VAL = 0x3f3f3f3f3f3f3f3f;

void run_case() {
  int n;
  cin >> n;
  vector<ll> seq(1); // seq is initialized with one element to avoid boundary checks
  for (int i = 1; i <= n; ++i) {
    ll val;
    cin >> val;
    // Maintain a monotonic increasing sequence by removing elements that are not smaller than current value
    while (val <= seq.back())
      seq.pop_back();
    seq.push_back(val);
  }
  n = seq.size() - 1; // Update n to the size of processed sequence

  vector<ll> dp(n + 2, INF_VAL); // dp[i] represents minimum cost from index i to end
  dp[n + 1] = 0; // Base case: no elements left means zero cost

  for (int i = n; i >= 1; --i) {
    // Default transition: take current element as a separate partition
    dp[i] = dp[i + 1] + 1;

    if (i != n) {
      // Determine thresholds for valid next partitions based on current element
      ll limit1 = max(seq[i + 1], 2 * seq[i]);
      ll limit2 = max(seq[i + 1], 3 * seq[i]);

      // Find the largest index with value <= limit1 using binary search
      int idx1 = upper_bound(seq.begin() + i + 1, seq.end(), limit1) - seq.begin() - 1;
      // Find the largest index with value <= limit2 using binary search
      int idx2 = upper_bound(seq.begin() + i + 1, seq.end(), limit2) - seq.begin() - 1;

      // Update dp[i] by considering both valid transitions
      dp[i] = min(dp[i], dp[idx1 + 1] + (seq[idx1] + seq[i] - 1) / seq[i]);
      dp[i] = min(dp[i], dp[idx2 + 1] + (seq[idx2] + seq[i] - 1) / seq[i]);
    }
  }
  cout << dp[1] << nl; // Output the minimum cost for full sequence
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--)
    run_case();
  return 0;
}


// https://github.com/VaHiX/CodeForces/