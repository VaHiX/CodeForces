// Problem: CF 2122 E - Greedy Grid Counting
// https://codeforces.com/contest/2122/problem/E

/*
E. Greedy Grid Counting
Algorithms/Techniques: Dynamic Programming with Transfer Updates
Time Complexity: O(n * k^2)
Space Complexity: O(n * k)

A path in a grid is called greedy if it starts at the top-left cell and moves only to the right or downward,
always moving to its neighbor with the greater value (or either if the values are equal).
The value of a path is the sum of the values of the cells it visits.
Given a partially filled 2×n grid of integers between 1 and k, count the number of ways to fill
the empty cells such that in every subgrid, there exists a greedy path that achieves the maximum value
out of all down/right paths.

This solution uses dynamic programming with transfer updates. For each column, we calculate how many
ways we can reach a certain value at the current position based on the previous positions.
We process columns from right to left, and for each cell in the grid (when it's unfilled), we try all 
possible values and update the DP accordingly.

*/

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <utility>

using namespace std;
typedef complex<double> base;
typedef long long ll;
typedef long double ld;
const double PI = acos(-1);
const ll mod = 998244353;
ll dp[2][505];
ll arr[2][505];

void clear(int p) {
  for (int i = 0; i < 505; i++) {
    dp[p][i] = 0;
  }
}

void print_dp(int p) {
  for (int i = 0; i <= 20; i++) {
    cout << dp[p][i] << " ";
  }
  cout << "\n";
}

void update(int p, int q, int plus, ll multiply = 1) {
  // Perform the transfer update based on 'plus' value
  for (int i = 0; i <= 501; i++) {
    if (plus < 0) {
      if (i + plus <= 0) {
        dp[q][max(0, i + plus)] =
            (dp[q][max(0, i + plus)] + dp[p][i] * multiply) % mod;
      }
    } else {
      dp[q][min(501, i + plus)] =
          (dp[q][min(501, i + plus)] + dp[p][i] * multiply) % mod;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < n; j++) {
        cin >> arr[i][j];
      }
    }

    clear(0);
    clear(1);
    dp[0][0] = 1;
    int p = 0, q = 1;

    // Process all columns from right to left
    for (int i = n - 1; i >= 1; i--) {
      if (arr[0][i] != -1 and arr[1][i - 1] != -1) {
        // Both current and previous column values are fixed
        int plus = arr[0][i] - arr[1][i - 1];
        update(p, q, plus);
      } else if (arr[0][i] != -1) {
        // Current cell is fixed but previous cell is unfilled
        for (int j = 1; j <= k; j++) {
          int plus = arr[0][i] - j;
          update(p, q, plus);
        }
      } else if (arr[1][i - 1] != -1) {
        // Previous cell is fixed but current cell is unfilled
        for (int j = 1; j <= k; j++) {
          int plus = j - arr[1][i - 1];
          update(p, q, plus);
        }
      } else {
        // Both cells are unfilled - we need to consider all combinations
        ll multiply = 0;
        for (int plus = 1 - k; plus <= k - 1; plus++) {
          if (plus <= 0) {
            multiply++;
          } else {
            multiply--;
          }
          update(p, q, plus, multiply);
        }
      }
      swap(p, q);
      clear(q);
    }

    ll ans = 0;
    for (int i = 0; i <= 501; i++) {
      ans = (ans + dp[p][i]) % mod;
    }

    // Final adjustment if starting cells are unfilled
    if (arr[0][0] == -1) {
      ans = ans * k % mod;
    }
    if (arr[1][n - 1] == -1) {
      ans = ans * k % mod;
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/