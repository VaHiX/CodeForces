// Problem: CF 2073 J - Gathering Sharks
// https://codeforces.com/contest/2073/problem/J

/*
 * Gathering Sharks
 * 
 * Problem Description:
 * You are the leader of a swarm of n sharks living in a one-dimensional ocean.
 * Initially, each shark forms its own group. You can command sharks to merge groups
 * by moving a group to the position of another smaller-numbered group. The goal is
 * to minimize the total time required for all sharks to gather into one group.
 *
 * Algorithm:
 * This problem uses dynamic programming with interval DP. We define f[i][j] as the
 * minimum time to merge all sharks in the range [i, j] into a single group, where
 * the final merged group number is the maximum group number in that range.
 * The recurrence considers merging two subsegments, with the cost being the distance
 * between the positions of the merging groups.
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 510;
int n, a[N], p[N], f[N][N];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[a[i]] = i; // Store the position of each shark by its group number
  for (int l = 1; l < n; l++) { // Iterate over all possible interval lengths
    for (int j = 1; j + l <= n; j++) { // For each starting index
      int k = j + l;
      f[j][k] = 1e6; // Initialize with large value
      for (int i = j + 1; i <= k; i++) { // Try all possible split points
        // f[j][i-1] + f[i][k] represents combining two parts
        // abs(p[i] - p[j]) is the cost to move group i's sharks to position of group j
        f[j][k] = min(f[j][k], f[j][i - 1] + f[i][k] + abs(p[i] - p[j]));
      }
    }
  }
  cout << f[1][n] << endl; // Minimum time for merging all sharks into one group
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(), cout.tie();
  solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/