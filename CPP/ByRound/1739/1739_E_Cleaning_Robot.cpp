// Problem: CF 1739 E - Cleaning Robot
// https://codeforces.com/contest/1739/problem/E

/*
 * Problem: Cleaning Robot
 * 
 * Algorithm/Technique: Dynamic Programming with Memoization
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * The problem involves a robot cleaning a hallway represented as a 2xN grid.
 * The robot starts at (1,1) and always moves to the closest dirty cell.
 * If multiple closest cells exist, the robot malfunctions.
 * 
 * We use dynamic programming to determine the maximum number of dirty cells
 * that can be left such that the robot never faces a tie in choosing the
 * closest dirty cell.
 * 
 * The DP state dp[p][q][r] represents the maximum number of dirty cells we
 * can leave in the subproblem starting at column p, with current row q,
 * and flag r indicating if we've just moved from the opposite row (r=1) or not (r=0).
 * 
 * Key idea:
 * - We track the maximum number of dirty cells that can be cleaned,
 *   ensuring that at each step, there's a unique closest dirty cell.
 * - The algorithm explores both possibilities: 
 *   1. Move to the same row (no need to track previous row)
 *   2. Move to the opposite row (if there's a dirty cell there and we're not restricted)
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int dp[200005][2][2];
string s[2];
int n;
int dpp(int p, int q, int r) {
  int &ans = dp[p][q][r];
  if (p == n)
    ans = 0;
  if (~ans)
    return ans;
  int id = s[q][p] - '0';
  ans = id + dpp(p + 1, q, 0);
  if (s[1 - q][p] == '1' && !r)
    ans = max(id + 1 + dpp(p + 1, 1 - q, 1), ans);
  return ans;
}
int main() {
  memset(dp, -1, sizeof(dp));
  scanf("%d", &n), cin >> s[0] >> s[1];
  printf("%d", dpp(0, 0, 0));
  return 0;
}


// https://github.com/VaHiX/CodeForces/