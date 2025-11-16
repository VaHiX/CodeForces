// Problem: CF 1874 D - Jellyfish and Miku
// https://codeforces.com/contest/1874/problem/D

/*
 * Problem: Jellyfish and Miku
 * 
 * Approach:
 * This is a dynamic programming problem where we aim to minimize the expected number of days
 * to reach city n from city 0 by optimally assigning beauties to roads under a constraint.
 * 
 * The idea is to use dynamic programming with the state f[i][j] representing the minimum
 * expected number of days to reach city i with a total beauty sum of j.
 * 
 * Key Insight:
 * For each city i and total beauty j, we consider all possible beauty values k for the
 * (i-1)th road. The recurrence relation is derived from the expected value calculation
 * involving probabilities of moving along edges.
 * 
 * Time Complexity: O(n * m^2)
 * Space Complexity: O(n * m)
 * 
 * Algorithms/Techniques:
 * - Dynamic Programming
 * - Optimization with bounded iterations
 * 
 */

#include <stdio.h>
#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int n, m, k;
double f[3005][3005];

void solv() {
  cin >> n >> m;
  f[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= m; j++) {
      f[i][j] = 1e9;
      // Iterate over possible beauty values k for the current road
      for (int k = 1; j - k >= i - 1 && k * (n - i) <= m - j; k++) {
        // g represents the expected time to reach the final city
        // using current assignment of beauty k
        double g = f[i - 1][j - k] + (double)(j - k) / k;
        if (g < f[i][j]) {
          f[i][j] = g;
        }
      }
    }
  }
  // Final answer is computed using the derived formula
  printf("%.15lf\n", f[n][m] * 2 + n);
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  while (T--)
    solv();
  return 0;
}


// https://github.com/VaHiX/CodeForces/