// Problem: CF 2028 D - Alice's Adventures in Cards
// https://codeforces.com/contest/2028/problem/D

/*
D. Alice's Adventures in Cards

Purpose:
This code determines if Alice can trade cards from type 1 to type n using three players (Queen, King, Jack) with their own preference orderings.
Alice trades according to her own preferences (higher number is better), while each player trades only if they value the card being given higher than the one received.

Algorithms/Techniques:
- Dynamic Programming with backward tracking
- Permutation-based comparison for valid trades
- Greedy-like logic in updating minimum indices

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing preferences and auxiliary arrays

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
const int maxn = 2e5 + 10;
const string S = "qkj";
int n;
int p[5][maxn];
void solve() {
  cin >> n;
  for (int j = 1; j <= 3; j++) {     // Read the preferences of Queen, King, and Jack
    for (int i = 1; i <= n; i++) {
      cin >> p[j][i];
    }
  }
  vector<int> Min(4, n);            // Min[j] stores the index of smallest value for player j so far
  vector<pair<int, int>> dp(n + 10, {-1, -1}); // dp[i] = {player, next_index} if a valid trade exists from card i
  for (int i = n - 1; i >= 1; i--) { // Process backwards from last to first card
    int win = -1;
    for (int j = 1; j <= 3; j++) {   // Check which player has a higher value than current (to trade)
      if (p[j][i] > p[j][Min[j]])
        win = j;
    }
    if (win == -1)                   // No valid trade from here
      continue;
    dp[i] = {win, Min[win]};         // Record the trade: player 'win' to get card at Min[win]
    for (int j = 1; j <= 3; j++) {   // Update minimums for each player
      if (p[j][i] < p[j][Min[j]]) {
        Min[j] = i;
      }
    }
  }
  if (dp[1].first == -1) {           // If no way to get from card 1
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  vector<pair<int, int>> ans = {dp[1]};  // Start trace back with first trade
  while (ans.back().second >= 0) {       // Continue until end of path
    ans.push_back(dp[ans.back().second]);
  }
  ans.pop_back();                        // Remove trailing -1
  cout << ans.size() << "\n";
  for (auto p : ans) {
    cout << S[p.first - 1] << " " << p.second << "\n";  // Output the path using q/k/j
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/