// Problem: CF 2143 D2 - Inversion Graph Coloring (Hard Version)
// https://codeforces.com/contest/2143/problem/D2

/*
D2. Inversion Graph Coloring (Hard Version)
Algorithm: Dynamic Programming with Binary Indexed Tree (Fenwick Tree)
Time Complexity: O(n^2 * log n) per test case
Space Complexity: O(n^2) for dp and BIT arrays

This problem counts the number of "good" subsequences in a given sequence.
A subsequence is good if it's possible to color its elements red or blue such that,
for every pair where element i > element j, they have different colors.

The approach uses dynamic programming combined with two Binary Indexed Trees (BITs)
to efficiently count valid transitions and maintain state while iterating through
the array in a nested fashion.
*/

#include <time.h>
#include <iostream>
#include <random>

#define ll long long
#define ull unsigned long long
#define lowbit(i) (i & -i)
#define rand() (myrand())
using namespace std;
mt19937 myrand(time(0));
const int maxn = 2e3 + 5;
const int mod = 1e9 + 7;
int n, _, a[maxn], tr[maxn][maxn][2], dp[maxn][maxn];

// Modify BIT: Update value at position x with increment y for key k and type t
void modify(int k, int x, int y, int t) {
  while (x <= n) {
    tr[k][x][t] = (tr[k][x][t] + y) % mod; // accumulate the value
    x += lowbit(x); // move to parent node
  }
}

// Get prefix sum from BIT up to position x for key k and type t
int get(int k, int x, int t) {
  int res = 0;
  while (x) {
    res = (res + tr[k][x][t]) % mod; // sum values along the path
    x -= lowbit(x); // move to parent node
  }
  return res;
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = 1; // Initialize first state
    for (int j = 1; j < i; ++j) {
      if (a[j] > a[i]) {
        // If previous element is greater than current, update transitions
        dp[j][i] = (dp[j][i] + get(j, a[i], 0)) % mod; // Get value from BIT for type 0
        dp[j][i] = (dp[j][i] + dp[j][0]) % mod; // Add base value
        modify(i, a[j], dp[j][i], 1); // Update BIT with new value for type 1
        modify(j, a[i], dp[j][i], 0); // Update BIT with new value for type 0
      } else {
        // If current element is greater or equal, update transitions in reverse
        dp[i][0] = (dp[i][0] + dp[j][0]) % mod; // Accumulate number of good sequences
        dp[i][j] = (dp[i][j] + get(j, a[i], 1)) % mod; // Get value from BIT for type 1
        modify(j, a[i], dp[i][j], 1); // Update BIT with new value for type 1
        modify(i, a[j], dp[i][j], 0); // Update BIT with new value for type 0
      }
    }
  }
  int ans = 1; // Start with empty subsequence count
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      ans = (ans + dp[i][j]) % mod;
      dp[i][j] = tr[i][j][0] = tr[i][j][1] = 0; // Reset values
    }
  }
  cout << ans << '\n';
}

signed main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/