// Problem: CF 2130 F - Permutation Blackhole
// https://codeforces.com/contest/2130/problem/F

/*
F. Permutation Blackhole
Algorithms/Techniques: Dynamic Programming with Memoization, Combination Mathematics
Time Complexity: O(n^4 * k^2) where n is the length of the sequence and k=12 is the maximum possible value for constraints
Space Complexity: O(n^4 * k^2) for the DP and sum arrays

The problem involves counting valid permutations that match an incomplete coloring sequence.
Each cell's score depends on the nearest black cell when it's colored. This is modeled via 
a recursive DP approach where we consider how to split segments of the permutation, 
and for each split point, we track constraints (left/right) on how many cells can be "scored".

The solution uses:
1. Dynamic Programming over intervals [left, right] in permutation
2. State tracking: left_constraint and right_constraint representing how many
   steps from either end are constrained by the coloring sequence
3. Combination numbers for splitting points
4. Prefix sums (sum_left, sum_right) to speed up transitions

This technique allows us efficiently compute the number of valid permutations that respect
the known values in the color sequence and produce matching outputs.
*/

#include <string.h>
#include <iostream>

using namespace std;
using ll = long long;
constexpr int MOD = 998244353;
const int MAX_N = 110;
const int MAX_K = 12;
ll n;
ll dp[MAX_N][MAX_N][MAX_K][MAX_K];
ll comb[MAX_N][MAX_N];
ll sum_left[MAX_N][MAX_N][MAX_K];
ll sum_right[MAX_N][MAX_N][MAX_K];
ll sequence[MAX_N];

void solve() {
  cin >> n;
  bool has_invalid_value = false;
  ll total_sum = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> sequence[i];
    total_sum += sequence[i];
    if (sequence[i] >= 12) {
      has_invalid_value = true;
    }
  }
  if (has_invalid_value || total_sum > n - 1) {
    cout << "0\n";
    return;
  }
  // Reset DP and sum arrays for each test case
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= n + 1; ++j) {
      memset(sum_left[i][j], 0, sizeof(sum_left[i][j]));
      memset(sum_right[i][j], 0, sizeof(sum_right[i][j]));
    }
  }
  // Iterate over all interval lengths
  for (int len = 1; len <= n + 1; ++len) {
    for (int left = 0; left + len <= n + 1; ++left) {
      int right = left + len;
      // For each interval [left, right], evaluate all combinations of constraints
      for (int left_constraint = 0; left_constraint < MAX_K;
           ++left_constraint) {
        for (int right_constraint = 0; right_constraint < MAX_K;
             ++right_constraint) {
          // Early pruning: impossible configurations
          if (left_constraint + right_constraint > right - left + 1) {
            dp[left][right][left_constraint][right_constraint] = 0;
            continue;
          }
          // Base case: single element interval (no splits possible)
          if (left + 1 == right) {
            dp[left][right][left_constraint][right_constraint] =
                ((left_constraint == 0 && right_constraint == 0) ? 1 : 0);
            sum_left[left][right][left_constraint] =
                (sum_left[left][right][left_constraint] +
                 dp[left][right][left_constraint][right_constraint]) %
                MOD;
            sum_right[left][right][right_constraint] =
                (sum_right[left][right][right_constraint] +
                 dp[left][right][left_constraint][right_constraint]) %
                MOD;
            continue;
          }
          ll count = 0;
          // Try every possible split point
          for (int split = left + 1; split <= right - 1; ++split) {
            if (sequence[split] != -1) {
              // If split point has a fixed value, enumerate all legal divisions
              for (int left_part = 0; left_part <= sequence[split];
                   ++left_part) {
                int right_part = sequence[split] - left_part;
                if ((split - left <= right - split && left != 0) ||
                    right == n + 1) {
                  // Left side constraint is applied
                  if (left_constraint > 0) {
                    count =
                        (count +
                         comb[right - left - 2][split - left - 1] *
                             dp[left][split][left_constraint - 1][left_part] %
                             MOD *
                             dp[split][right][right_part][right_constraint]) %
                        MOD;
                  }
                } else {
                  // Right side constraint is applied
                  if (right_constraint > 0) {
                    count =
                        (count +
                         comb[right - left - 2][split - left - 1] *
                             dp[left][split][left_constraint][left_part] % MOD *
                             dp[split][right][right_part]
                               [right_constraint - 1]) %
                        MOD;
                  }
                }
              }
            } else {
              // If split point is unknown, use accumulated sums for faster computation
              if ((split - left <= right - split && left != 0) ||
                  right == n + 1) {
                if (left_constraint > 0) {
                  count =
                      (count + comb[right - left - 2][split - left - 1] *
                                   sum_left[left][split][left_constraint - 1] %
                                   MOD *
                                   sum_right[split][right][right_constraint]) %
                      MOD;
                }
              } else {
                if (right_constraint > 0) {
                  count = (count +
                           comb[right - left - 2][split - left - 1] *
                               sum_left[left][split][left_constraint] % MOD *
                               sum_right[split][right][right_constraint - 1]) %
                          MOD;
                }
              }
            }
          }
          dp[left][right][left_constraint][right_constraint] = count;
          sum_left[left][right][left_constraint] =
              (sum_left[left][right][left_constraint] + count) % MOD;
          sum_right[left][right][right_constraint] =
              (sum_right[left][right][right_constraint] + count) % MOD;
        }
      }
    }
  }
  ll result = 0;
  // Sum all valid configurations
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      result = (result + dp[0][n + 1][i][j]) % MOD;
    }
  }
  cout << result << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  comb[0][0] = 1;
  // Precompute combinations
  for (int i = 1; i <= 105; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (j == 0) {
        comb[i][j] = 1;
      } else {
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
      }
    }
  }
  int test_cases;
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/