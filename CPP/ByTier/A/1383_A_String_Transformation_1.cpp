// Problem: CF 1383 A - String Transformation 1
// https://codeforces.com/contest/1383/problem/A

/*
 * Problem: String Transformation 1
 * Description:
 *   Koa the Koala has two strings A and B of same length n. In one move,
 *   she can select a subset of positions where A[p1] = A[p2] = ... = x
 *   (all same letter), then choose a letter y > x, and set all those
 *   positions to y. Goal is to make A equal to B with minimum moves,
 *   or return -1 if impossible.
 *
 * Approach:
 *   1. For each position i, check that s[i] <= t[i]. If not, return -1.
 *   2. Build a 26x26 matrix 'b' where b[x][y] = 1 means we can directly
 *      transform character x to y (i.e., there exists a position where A[i]=x and B[i]=y).
 *   3. For each character c from 'a' to 't', scan forward until finding
 *      a character d such that b[c][d] = 1.
 *   4. When found, increment result count, and propagate this transformation
 *      to all characters: for every k where b[c][k]=1, set b[d][k]=1.
 *   5. Return the total number of steps (ans).
 *
 * Time Complexity: O(26 * 26 * n) = O(n) since 26 is constant
 * Space Complexity: O(26 * 26) = O(1) since 26 is constant
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
  int n, ans = 0;
  string s, t;
  cin >> n >> s >> t;
  vector<vector<int>> b(26, vector<int>(26));
  for (int i = 0; i < n; i++)
    if (s[i] > t[i]) {
      cout << "-1\n";
      return;
    } else
      b[s[i] - 'a'][t[i] - 'a'] = 1; // Mark direct transformation possible
  for (int i = 0; i < 26; i++) {
    int j = i + 1;
    while (j < 26 && !b[i][j])
      j++;
    if (j < 26) {
      ans++; // Found a valid transformation step
      for (int k = i; k < 26; k++)
        if (b[i][k])
          b[j][k] = 1; // Propagate the transformation
    }
  }
  cout << ans << "\n";
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/