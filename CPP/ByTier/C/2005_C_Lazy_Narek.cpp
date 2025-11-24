// Problem: CF 2005 C - Lazy Narek
// https://codeforces.com/contest/2005/problem/C

/*
C. Lazy Narek
Algorithms/Techniques: Dynamic Programming with State Compression
Time Complexity: O(n * m * 5) per test case, where n is number of strings and m is length of each string
Space Complexity: O(n * 5) for the DP table

The problem involves selecting a subset of strings to maximize the difference between Narek's score (score_n) and ChatGPT's score (score_c).
Narek's score is calculated by finding complete "narek" subsequences with greedy matching.
ChatGPT's score is the count of unused letters from Narek's failed attempts.

The DP state dp[i][j] represents the maximum score difference achievable up to string i, ending in state j (0-4), which corresponds to:
0: Finished a "narek" sequence
1: Found 'n'
2: Found 'na'
3: Found 'nar'
4: Found 'nare'

We calculate for each string how many points we would gain or lose by appending it and update DP accordingly.
Finally, the result is computed based on final state values adjusted by penalties for incomplete "narek" sequences.

*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int t, n, m, dp[100005][5], now, cnt;
string s, e = "narek";
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> t;
  dp[0][1] = dp[0][2] = dp[0][3] = dp[0][4] = 0xcfcfcfcf; // Initialize states with large negative values
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> s;
      // Copy previous state values
      dp[i][0] = dp[i - 1][0], dp[i][1] = dp[i - 1][1], dp[i][2] = dp[i - 1][2],
      dp[i][3] = dp[i - 1][3], dp[i][4] = dp[i - 1][4];
      for (int j = 0; j < 5; j++) { // Try starting from each possible current state
        now = j;
        cnt = 0;
        for (int k = 0; k < m; k++) {
          if (s[k] == e[now]) { // If character matches expected letter in 'narek'
            now = (now + 1) % 5; // Move to next required letter
            cnt++; // Increment points for matching valid character
          } else if (s[k] == 'n' || s[k] == 'a' || s[k] == 'r' || s[k] == 'e' ||
                     s[k] == 'k') { // If it's one of the target letters but not next expected
            cnt--; // Penalty for consuming a letter that does not complete a sequence
          }
        }
        dp[i][now] = max(dp[i][now], dp[i - 1][j] + cnt); // Update DP with best value obtained so far
      }
    }
    // Final result considers penalty for incomplete "narek" sequences ending at different states
    cout << max(max(max(dp[n][0], dp[n][1] - 2), dp[n][2] - 4),
                max(dp[n][3] - 6, dp[n][4] - 8))
         << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/