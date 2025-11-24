// Problem: CF 1769 C2 - Подкрутка II
// https://codeforces.com/contest/1769/problem/C2

/*
 * Problem: C2. Подкрутка II (Tuning II)
 * 
 * Algorithm: Dynamic Programming with Sliding Window Approach
 * 
 * Time Complexity: O(n + max_day), where n is the number of commits and max_day is the maximum day number
 * Space Complexity: O(max_day), since we use a DP array up to 1e6 + 5
 * 
 * Approach:
 * - For each commit at day `a[i]`, we consider two possibilities:
 *   1. Commit is kept at day `a[i]`
 *   2. Commit is moved forward to day `a[i] + 1`
 * - We precompute the maximum number of consecutive days that can be covered
 *   by considering both possibilities for each commit.
 * - Using a dynamic programming array `dp` where `dp[i]` stores the maximum length
 *   of consecutive days ending at day `i`.
 * 
 * The key idea is that for each commit, we look at:
 *   - How many consecutive days can be covered if this commit is at day `a[i]` (we add 1 to dp[a[i] - 1])
 *   - How many consecutive days can be covered if this commit is at day `a[i] + 1` (we add 1 to dp[a[i]])
 * 
 * We process all commits in order and update dp array accordingly.
 * Finally, we find the maximum among all dp values.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = (int)1e6 + 5;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> dp(N);
  for (int i = 0; i < n; i++) {
    // Update DP for the day the commit is kept
    dp[a[i] + 1] = dp[a[i]] + 1;
    // Update DP for the day the commit is moved forward
    dp[a[i]] = dp[a[i] - 1] + 1;
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n';
}
int main() {
  int _ = 1;
  cin >> _;
  while (_--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/