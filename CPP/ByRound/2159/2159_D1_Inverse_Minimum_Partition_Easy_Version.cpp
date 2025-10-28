// Problem: CF 2159 D1 - Inverse Minimum Partition (Easy Version)
// https://codeforces.com/contest/2159/problem/D1

/*
Problem: Inverse Minimum Partition (Easy Version)

This problem involves partitioning a sequence to minimize the total cost,
where the cost of a subsequence is defined as ceil(k / min_element) where k is the length.

Algorithm:
- Preprocess rightmost minimum indices using dynamic programming.
- Use another DP to compute minimal cost partition.
- For each position, try multiplying by 2 and 3 to find valid next partitions.

Time Complexity: O(n * log(max(a[i]))) per test case
Space Complexity: O(n)

Techniques Used:
- Dynamic Programming
- Preprocessing with suffix minimums
- Binary search using upper_bound
*/

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &i : a)
      cin >> i;
    vector<int> rightmost_min(n + 1);
    rightmost_min[n] = n; // Base case: no elements to the right
    rightmost_min[n - 1] = n - 1; // Last element's rightmost min is itself
    for (int i = n - 2; i >= 0; i--) {
      if (a[i] < a[rightmost_min[i + 1]]) {
        rightmost_min[i] = i; // Current element is smaller than rightmost minimum, so it is new minimum
      } else {
        rightmost_min[i] = rightmost_min[i + 1]; // Otherwise inherit the rightmost minimum index
      }
    }
    vector<long long> b;
    int idx = rightmost_min[0];
    while (idx < n) {
      b.push_back(a[idx]); // Build the sequence of rightmost minimums
      idx = rightmost_min[idx + 1]; // Move to next partition point
    }
    int m = b.size();
    vector<int> dp(m + 1);
    dp[m] = 0; // Base case: no elements left, cost is zero
    dp[m - 1] = 1; // If one element remains, cost is 1
    for (int i = m - 2; i >= 0; i--) {
      dp[i] = 1 + dp[i + 1]; // Take current as a separate part, and continue from next
      for (auto &mult : {2, 3}) {
        int j = upper_bound(b.begin(), b.end(), mult * b[i]) - b.begin(); // Find first value > mult * b[i]
        dp[i] = min(dp[i], mult + dp[j]); // Try to extend current range by multiplying with 2 or 3
      }
    }
    cout << dp[0] << "\n"; // Final result for this test case
  }
}


// https://github.com/VaHiX/CodeForces/