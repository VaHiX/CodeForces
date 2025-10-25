// Problem: CF 2070 F - Friends and Pizza
// https://codeforces.com/contest/2070/problem/F

/*
F. Friends and Pizza
Algorithms/Techniques: Subset DP with bitmask optimization, inclusion-exclusion principle

Time Complexity: O(2^n * n + m * 2^n)
Space Complexity: O(2^n * n)

The problem involves counting pairs of friends such that:
1. They don't quarrel (i.e. no pizza with odd number of slices is liked by both).
2. Monocarp eats exactly k slices.

This is solved by:
1. Encoding friend preferences as bitmasks.
2. Using subset DP to count valid combinations for each subset of friends and odd pizza counts.
3. Applying inclusion-exclusion to avoid overcounting.
4. Finally, computing result for each k based on how many slices Monocarp eats in that case.

*/

#include <iostream>
#include <string>

using namespace std;
int n, m;
int bitmask[5 << 17]; // Stores bitmasks of friends' pizza preferences
int dp[1 << 20][21];   // dp[mask][odd_count] = number of ways to select subset with given odd count
long long count[1 << 20][21]; // Helper for storing combinations
int weights[20];
long long result[4 << 17]; // Final answer for each k

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    string str;
    cin >> str;
    for (char c : str)
      bitmask[i] |= 1 << c - 'A'; // Set bits according to friend's preferred pizzas
  }
  int oddBitmask = 0, totalSum = 0;
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
    if (weights[i] % 2 == 1)
      oddBitmask |= 1 << i; // Mark indices of pizzas with odd slices
    totalSum += weights[i];
  }
  // Initialize dp for all masks
  for (int i = 0; i < m; i++)
    dp[bitmask[i]][__builtin_popcount(bitmask[i] & oddBitmask)]++; // Count friends based on how many odd pizza they share

  int oddCount = __builtin_popcount(oddBitmask); // Total number of odd-pizza indices
  // Subset DP: propagate counts from smaller subsets to larger ones
  for (int k = 0; k < n; k++)
    for (int i = 0; i < 1 << n; i++)
      if (i >> k & 1) {
        for (int j = 0; j <= oddCount; j++)
          dp[i][j] += dp[i ^ (1 << k)][j]; // Add counts from subsets missing k-th pizza
      }

  // Count pairs: for each subset, compute how many combinations are possible
  for (int i = 0; i < 1 << n; i++) {
    for (int j = 0; j <= oddCount; j++) {
      if (j + j <= oddCount)
        count[i][j + j] += (long long)dp[i][j] * (dp[i][j] - 1) / 2; // C(n,2) for same odd count
      for (int k = j + 1; j + k <= oddCount; k++)
        count[i][j + k] += (long long)dp[i][j] * dp[i][k]; // Pairs with different odd counts
    }
  }

  // Inclusion-exclusion: remove double-counted subsets
  for (int k = 0; k < n; k++)
    for (int i = 0; i < 1 << n; i++)
      if (i >> k & 1) {
        for (int j = 0; j <= oddCount; j++)
          count[i][j] -= count[i ^ (1 << k)][j]; // Subtract subsets excluding k-th element
      }

  // Final result calculation: compute contributions of each mask
  for (int i = 0; i < 1 << n; i++) {
    int oddBits = __builtin_popcount(i & oddBitmask); // Count odd pizzas in this mask
    int remainingWeight = 0;
    for (int j = 0; j < n; j++)
      if (!(i >> j & 1)) // If the pizza is not in current subset, Monocarp eats it
        remainingWeight += weights[j];
    result[remainingWeight] += count[i][oddBits]; // Add to final result
  }

  for (int i = 0; i <= totalSum; i++)
    cout << result[i] << (i == totalSum ? "\n" : " ");
}


// https://github.com/VaHiX/codeForces/