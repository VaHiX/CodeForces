

/**
 * @file 2130_F_Permutation_Blackhole.cpp
 * @brief Solution for Codeforces problem 2130F - Permutation Blackhole
 *
 * Problem: Count the number of valid permutations where each element's value
 * equals the length of the longest increasing or decreasing subsequence ending
 * at that position.
 *
 * Approach: Dynamic Programming with combinatorial counting
 * Time Complexity: O(n^4 * k^3) where n is the maximum array size (100) and k
 * is the maximum value (11) Space Complexity: O(n^2 * k^2) for the DP tables
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MOD = 998244353;
const int MAX_N = 110;
const int MAX_K = 12;

ll n;
ll dp[MAX_N][MAX_N][MAX_K][MAX_K]; // dp[l][r][x][y]: count for interval [l,r]
                                   // with x left and y right constraints
ll comb[MAX_N][MAX_N];             // Combination numbers (n choose k)
ll sum_left[MAX_N][MAX_N][MAX_K];  // Prefix sums for left constraints
ll sum_right[MAX_N][MAX_N][MAX_K]; // Prefix sums for right constraints
ll sequence[MAX_N];                // Input sequence

/**
 * Solves a single test case for the problem
 */
void solve() {
  cin >> n;
  bool has_invalid_value = false;
  ll total_sum = 0;

  // Read input and check for invalid values
  for (int i = 1; i <= n; ++i) {
    cin >> sequence[i];
    total_sum += sequence[i];
    if (sequence[i] >= 12) {
      has_invalid_value = true;
    }
  }

  // Early exit if constraints are impossible to satisfy
  if (has_invalid_value || total_sum > n - 1) {
    cout << "0\n";
    return;
  }

  // Initialize DP tables
  for (int i = 0; i <= n + 1; ++i) {
    for (int j = 0; j <= n + 1; ++j) {
      memset(sum_left[i][j], 0, sizeof(sum_left[i][j]));
      memset(sum_right[i][j], 0, sizeof(sum_right[i][j]));
    }
  }

  // Main DP computation
  for (int len = 1; len <= n + 1; ++len) {
    for (int left = 0; left + len <= n + 1; ++left) {
      int right = left + len;

      for (int left_constraint = 0; left_constraint < MAX_K;
           ++left_constraint) {
        for (int right_constraint = 0; right_constraint < MAX_K;
             ++right_constraint) {
          // Skip invalid states where constraints exceed interval length
          if (left_constraint + right_constraint > right - left + 1) {
            dp[left][right][left_constraint][right_constraint] = 0;
            continue;
          }

          // Base case: single element interval
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

          // Try each possible split point in the interval
          for (int split = left + 1; split <= right - 1; ++split) {
            if (sequence[split] != -1) {
              // Handle fixed value in the sequence
              for (int left_part = 0; left_part <= sequence[split];
                   ++left_part) {
                int right_part = sequence[split] - left_part;
                if ((split - left <= right - split && left != 0) ||
                    right == n + 1) {
                  // Case 1: Left side is smaller or equal to right side
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
                  // Case 2: Right side is smaller
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
              // Handle wildcard value (-1) in the sequence
              if ((split - left <= right - split && left != 0) ||
                  right == n + 1) {
                // Case 1: Left side is smaller or equal to right side
                if (left_constraint > 0) {
                  count =
                      (count + comb[right - left - 2][split - left - 1] *
                                   sum_left[left][split][left_constraint - 1] %
                                   MOD *
                                   sum_right[split][right][right_constraint]) %
                      MOD;
                }
              } else {
                // Case 2: Right side is smaller
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

          // Update DP tables
          dp[left][right][left_constraint][right_constraint] = count;
          sum_left[left][right][left_constraint] =
              (sum_left[left][right][left_constraint] + count) % MOD;
          sum_right[left][right][right_constraint] =
              (sum_right[left][right][right_constraint] + count) % MOD;
        }
      }
    }
  }

  // Sum up all valid final states
  ll result = 0;
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

  // Precompute combination numbers using Pascal's triangle
  comb[0][0] = 1;
  for (int i = 1; i <= 105; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (j == 0) {
        comb[i][j] = 1;
      } else {
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
      }
    }
  }

  // Process multiple test cases
  int test_cases;
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }

  return 0;
}