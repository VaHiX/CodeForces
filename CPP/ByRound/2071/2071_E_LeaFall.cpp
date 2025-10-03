// Problem: CF 2071 E - LeaFall
// https://codeforces.com/contest/2071/problem/E

/*
E. LeaFall

Purpose:
This code computes the expected number of unordered pairs of distinct vertices that become leaves in a tree after each vertex independently falls with a given probability. The solution uses dynamic programming on trees to calculate contributions to the expectation.

Algorithms/Techniques:
- Tree Dynamic Programming (DP)
- Modular exponentiation
- Probability computation using modular inverse

Time Complexity: O(n * 4 * 3 * average_degree) per test case, which simplifies to O(n) for tree structures.
Space Complexity: O(n * 4 * 3) for DP states + O(n) for adjacency list storage = O(n)

*/

#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define eb emplace_back
#define endl '\n'
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vll vector<ll>
#define pll pair<ll, ll>
#define pii pair<int, int>
#define vpii vector<pii>
#define vpll vector<pll>
#define vvpi vector<vpii>
#define Yes cout << "YES" << endl;
#define No cout << "NO" << endl;
const ll MOD = 998244353;
vi line[100000];
ll p[100000], dp[100000][4][3], tdp[4][3];

// Fast modular exponentiation to compute a^b mod MOD
ll qpow(ll a, ll b) {
  ll ans = 1;
  while (b > 0) {
    if (b & 1)
      ans = ans * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return ans;
}

// DFS-based DP to compute probabilities of various states for each vertex
void dfs(int t, int f) {
  vi::iterator it;
  int i, j;

  // Initialize DP values for current node
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++)
      dp[t][i][j] = 0;
  }

  // Base case: probability that this vertex falls = p[t], otherwise doesn't fall
  dp[t][0][0] = p[t];                     // Node falls, so contributes to state (0,0)
  dp[t][1][0] = (1 + MOD - p[t]) % MOD;   // Node does not fall, so it's still a leaf or not a leaf
  dp[t][2][1] = (1 + MOD - p[t]) % MOD;   // Node has one adjacent edge remaining

  // Traverse child nodes
  for (it = line[t].begin(); it != line[t].end(); it++) {
    if (*it == f)
      continue;
    dfs(*it, t);

    // Reset temporary dp array
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 3; j++)
        tdp[i][j] = 0;
    }

    // Combine results from current node with subchild's results using state transitions
    for (i = 0; i <= 2; i++) {
      for (j = 0; i + j <= 2; j++) {
        tdp[0][i + j] =
            (tdp[0][i + j] +
             dp[t][0][i] * (dp[*it][0][j] + dp[*it][1][j] + dp[*it][3][j])) %
            MOD;
        tdp[1][i + j] =
            (tdp[1][i + j] +
             dp[t][1][i] * (dp[*it][0][j] + dp[*it][1][j] + dp[*it][2][j])) %
            MOD;
        tdp[2][i + j] = (tdp[2][i + j] + dp[t][2][i] * dp[*it][0][j]) % MOD;
        tdp[3][i + j] = (tdp[3][i + j] + dp[t][3][i] * dp[*it][0][j]) % MOD;
        tdp[3][i + j] =
            (tdp[3][i + j] + dp[t][2][i] * (dp[*it][1][j] + dp[*it][2][j])) %
            MOD;
      }
    }

    // Move values from temporary back to main dp array
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 3; j++) {
        dp[t][i][j] = tdp[i][j];
        tdp[i][j] = 0;
      }
    }
  }
}

void solve() {
  int n, i, u, v;
  ll a, b;
  cin >> n;

  // Read probabilities for each node
  for (i = 0; i < n; i++) {
    cin >> a >> b;
    p[i] = a * qpow(b, MOD - 2) % MOD;  // Modular inverse of b
  }

  // Build adjacency list for the tree
  for (i = 0; i < n - 1; i++) {
    cin >> u >> v;
    line[u - 1].pb(v - 1);
    line[v - 1].pb(u - 1);
  }

  // Perform DFS starting from root node 0
  dfs(0, -1);

  // Output result for unordered pairs where both vertices are leaves after falling
  cout << (dp[0][0][2] + dp[0][1][2] + dp[0][3][2]) % MOD << endl;

  // Clear the adjacency list for next test case
  for (i = 0; i < n; i++)
    line[i].clear();
}

int32_t main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/