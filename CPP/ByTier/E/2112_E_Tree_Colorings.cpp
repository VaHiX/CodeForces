// Problem: CF 2112 E - Tree Colorings
// https://codeforces.com/contest/2112/problem/E

/*
E. Tree Colorings
Algorithms/Techniques: Dynamic Programming, Number Theory, Preprocessing

Time Complexity: O(v * log v + t), where v = 5e5 and t is the number of test cases
Space Complexity: O(v), where v = 5e5

This problem involves finding the minimum number of vertices in a tree that has exactly m beautiful colorings.
The key insight is to model the structure using dynamic programming, where dp[i] represents the minimum number 
of vertices needed to achieve exactly i beautiful colorings. The recurrence relation uses the idea of 
splitting the count of colorings into divisors and combining their contributions.

The algorithm precomputes dp values for all possible m up to 5e5. It iterates over all integers i starting from 3
and updates the dp table using the recurrence derived from the combinatorial structure of the coloring rules.
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 5e5 + 5, v = 5e5;
int dp[maxn];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  for (int i = 1; i <= v; ++i)
    dp[i] = 1e9; // Initialize all dp values to infinity
  dp[1] = 1;     // Base case: one vertex tree has exactly 1 beautiful coloring
  for (int i = 3; i <= v; ++i) {
    for (int j = i; j <= v; j += i) {
      // Update dp[j] using the recurrence: dp[j] = min(dp[j], dp[i - 2] + dp[j / i])
      // This models combining colorings from two subtree structures
      dp[j] = min(dp[j], dp[i - 2] + dp[j / i]);
    }
  }
  int t;
  cin >> t;
  int m;
  while (t--) {
    cin >> m;
    if (dp[m] == 1e9)
      cout << "-1\n"; // No valid tree exists for this m
    else
      cout << dp[m] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/