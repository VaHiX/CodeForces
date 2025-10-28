// Problem: CF 2024 F - Many Games
// https://codeforces.com/contest/2024/problem/F

/*
Purpose: 
This code solves the "Many Games" problem where the goal is to maximize the expected value of winnings from a set of casino games.
Each game has a probability of winning and a payout. If you lose any game in the chosen set, you win nothing.
The expected value is calculated as (product of probabilities) * (sum of winnings) for the selected games.
We use dynamic programming with a greedy approach to optimize the selection of games.

Algorithms/Techniques:
- Greedy selection with sorting
- Dynamic Programming (0/1 knapsack-like DP with probability as weight)
- Optimization: handling 100% win probability games separately

Time Complexity: O(n log n + m * k) where n is number of games, m is max possible sum of winnings, k is the number of selected games
Space Complexity: O(m + n) where m is the maximum sum of winnings and n is the number of games
*/

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using db = double;
using i64 = signed long long int;
using u64 = unsigned long long int;
const int inf = 0x3f3f3f3f;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;

void solve() {
  int n;
  cin >> n;
  std::vector<array<int, 2>> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i][0] >> b[i][1]; // Read probability and winnings
  }
  int m = 2e5 + 6;
  // Sort by probability descending, then by winnings descending
  sort(b.begin(), b.end(), [](const auto &a, const auto &b) {
    if (a[0] != b[0])
      return a[0] > b[0];
    return a[1] > b[1];
  });
  db sum100 = 0; // Sum of winnings for 100% games
  vector<array<int, 2>> a; // Games to process with DP
  for (int i = 0; i < n;) {
    int e = i + 1;
    while (e < n && b[i][0] == b[e][0])
      e++;
    if (b[i][0] == 100) {
      // All 100% games are taken since they don't reduce probability
      for (int k = i; k < e; k++)
        sum100 += b[k][1];
      i = e;
      continue;
    }
    // Optimization: if the probability is too low, we can only take certain number of games
    int mx = (200 - b[i][0]) / (100 - b[i][0]) - 1;
    for (int k = i; k < e && k - i < mx; k++) {
      a.emplace_back(b[k]); // Take only up to a limit based on probability
    }
    i = e;
  }
  
  // Dynamic programming to find maximum probability for different sums of winnings
  vector<db> f(m + 1, -1); // f[i] = max probability to get sum i
  f[0] = 1;
  int top = 0; // Highest index with non-negative value
  
  // Iterate through all games and update probabilities
  for (int i = 0; i < a.size(); i++) {
    for (int j = top; j >= 0; j--) {
      if (f[j] <= 0)
        continue;
      int j2 = j + a[i][1]; // New sum of winnings
      if (j2 >= m)
        continue;
      top = max(top, j2);
      f[j2] = max(f[j2], f[j] * a[i][0] / 100.0); // Update probability
    }
  }
  
  db ans = sum100; // Start with all 100% games
  // Check all possible sums and calculate expected values
  for (int i = 1; i <= top; i++) {
    if (f[i] < 0)
      continue;
    ans = max(ans, (db)f[i] * (i + sum100)); // Expected value = probability * sum of winnings
  }
  cout << fixed << setprecision(8) << ans << endl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/