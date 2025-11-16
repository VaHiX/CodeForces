// Problem: CF 1854 E - Game Bundles
// https://codeforces.com/contest/1854/problem/E

/*
 * Code Purpose: This program solves the problem of constructing a set of game enjoyment values such that exactly 'm' distinct game bundles can be formed, where each bundle sums to 60.
 * 
 * Algorithm/Techniques: 
 * - Dynamic Programming (DP) is used to count the number of subsets that sum to a specific value.
 * - A brute-force search over small combinations is performed to find valid sets of values.
 * - For each candidate set, it calculates the number of subsets that sum to 60 and adjusts the set if needed.
 * 
 * Time Complexity: O(35^2 * 60^2) - due to nested loops over small values (up to 35) and DP computation for subset sums.
 * Space Complexity: O(60^2) - for the DP table used to count subset sums.
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define mod 1000000007
#define oo 1000000010
const int K = 61;
long long dp[K][K]; // DP table to store number of ways to achieve sum with given elements
long long m, n;

// Function to compute the number of subsets that sum to each value using dynamic programming
void get(vector<int> &v) {
  for (int i = 1; i < K; i++)
    dp[(int)v.size()][i] = 0;
  dp[(int)v.size()][0] = 1; // Base case: one way to get sum 0 (empty subset)
  for (int i = (int)v.size() - 1; i >= 0; i--) {
    for (int sum = 0; sum < K; sum++) {
      dp[i][sum] = dp[i + 1][sum]; // Don't take current element
      if (sum >= v[i])
        dp[i][sum] += dp[i + 1][sum - v[i]]; // Take current element
    }
  }
}

// Function to verify the solution and adjust if necessary
void check(vector<int> v) {
  get(v);
  n = m;
  if (dp[0][60] > n)
    return; // Too many bundles
  n -= dp[0][60]; // Reduce expected count by actual count
  int can = 60 - (int)v.size(); // How many more elements can be added
  int mx, val;
  while (can > 0 && n > 0) {
    mx = 1, val = 0;
    for (int i = 1; i < 30; i++) {
      if (dp[0][i] <= n && dp[0][i] > mx) {
        mx = dp[0][i];
        val = i;
      }
    }
    v.push_back(60 - val); // Add a value that leads to 'val' subsets
    n -= mx;
    can--;
  }
  if (n > 0)
    return; // Could not fully utilize m
  printf("%d\n", (int)v.size());
  for (int i = 0; i < (int)v.size(); i++) {
    printf("%d ", v[i]);
  }
  puts("");
  exit(0); // Solution found, exit
}

int main() {
  cin >> m;
  vector<int> v;
  for (int ones = 0; ones <= 35; ones++) { // Try different number of 1s
    for (int two = 0; two + ones <= 35; two++) { // Try different number of 2s
      v.clear();
      for (int i = 0; i < ones; i++)
        v.push_back(1);
      for (int i = 0; i < two; i++)
        v.push_back(2);
      check(v);
      while ((int)v.size() < 35)
        v.push_back(3);
      check(v);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/