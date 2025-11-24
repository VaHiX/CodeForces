// Problem: CF 474 D - Flowers
// https://codeforces.com/contest/474/problem/D

/*
 * Flower Dinner Problem
 *
 * Purpose:
 *   This program calculates the number of ways Marmot can eat flowers such that
 *   white flowers appear only in groups of exactly k flowers. The solution uses dynamic programming.
 *
 * Algorithm:
 *   - Use dynamic programming to precompute dp[i], which represents the number of valid ways
 *     to arrange flowers of length i.
 *   - A valid arrangement is one where white flowers appear in groups of exactly k.
 *   - Transitions:
 *     - dp[i] = dp[i - k] + dp[i - 1] (either add a red flower or a group of k whites)
 *   - Prefix sum is used to answer range queries efficiently.
 *
 * Time Complexity: O(N + T), where N = 1e5 (max flower count), T = number of test cases
 * Space Complexity: O(N), for dp array
 */

#include <cstring>
#include <iostream>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100005
#define mod 1000000007
using namespace std;

ll dp[N]; // dp[i] stores number of valid arrangements of i flowers

int main() {
  ll i, j, k; // loop variables
  ll n, m;   // number of test cases
  ll a, b;   // range limits for each test case

  cin >> n >> k; // read number of test cases and group size k

  // Initialize dp array: fill all values with 0
  memset(dp, 0, sizeof(dp));

  // Base cases
  // For lengths less than k, only one way (all red flowers)
  i = 1;
  while (i < k) {
    dp[i] = 1;
    i++;
  }

  // For length k, we can have either all reds (RR...R) or all whites (WW...W)
  dp[k] = 2;

  // Fill dp array using recurrence:
  // dp[i] = dp[i - k] + dp[i - 1]
  // We can form a sequence of i flowers by appending:
  //   - A red flower to any sequence of length i - 1
  //   - A group of k white flowers to any sequence of length i - k
  for (i = k + 1; i < N; i++) {
    dp[i] = (dp[i - k] % mod + dp[i - 1] % mod) % mod;
  }

  // Compute prefix sum to allow fast range queries
  for (i = 1; i < N; i++) {
    dp[i] = (dp[i] % mod + dp[i - 1] % mod) % mod;
  }

  // Process each test case
  for (i = 0; i < n; i++) {
    cin >> a >> b;
    // Calculate result for range [a, b]
    k = (dp[b] - dp[a - 1]) % mod;
    if (k < 0) // handle negative modulo correctly
      k += mod;
    cout << k << endl;
  }

  return 0;
}


// https://github.com/VaHiX/CodeForces/