// Problem: CF 706 C - Hard problem
// https://codeforces.com/contest/706/problem/C

/*
 * Problem: C. Hard problem
 * Algorithm: Dynamic Programming
 * Time Complexity: O(n), where n is the number of strings
 * Space Complexity: O(n), for storing dp array and string reversals
 *
 * Approach:
 * - For each string, we can either keep it as is or reverse it.
 * - We use dynamic programming where dp[i][0] represents the minimum energy
 *   to sort the first i+1 strings ending with the i-th string in its original form,
 *   and dp[i][1] represents the minimum energy to sort the first i+1 strings
 *   ending with the i-th string in reversed form.
 * - For each position i, we check if we can append the current string (original or reversed)
 *   to the previous state (original or reversed) while maintaining lexicographical order.
 */

#include <algorithm>
#include <iostream>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define inf 1000000000000000
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, x;
  cin >> n;
  ll a[n]; // energy cost to reverse each string
  for (i = 0; i < n; i++)
    cin >> a[i];
  string s[n], r[n]; // s[i] is original, r[i] is reversed
  ll dp[n][2]; // dp[i][0] = cost ending with s[i], dp[i][1] = cost ending with r[i]
  for (i = 0; i < n; i++) {
    cin >> s[i];
    r[i] = s[i];
    reverse(r[i].begin(), r[i].end()); // reverse the string
    dp[i][0] = inf;
    dp[i][1] = inf;
  }
  dp[0][0] = 0; // first string not reversed
  dp[0][1] = a[0]; // first string reversed
  for (i = 1; i < n; i++) {
    // Check if we can append original string s[i] after original s[i-1]
    if (s[i - 1] <= s[i])
      dp[i][0] = dp[i - 1][0];
    // Check if we can append original string s[i] after reversed s[i-1]
    if (s[i] >= r[i - 1])
      dp[i][0] = min(dp[i][0], dp[i - 1][1]);
    // Check if we can append reversed string r[i] after original s[i-1]
    if (r[i] >= s[i - 1])
      dp[i][1] = dp[i - 1][0] + a[i];
    // Check if we can append reversed string r[i] after reversed s[i-1]
    if (r[i] >= r[i - 1])
      dp[i][1] = min(dp[i][1], dp[i - 1][1] + a[i]);
  }
  x = min(dp[n - 1][0], dp[n - 1][1]);
  if (x == inf)
    cout << "-1";
  else
    cout << x;
  return 0;
}


// https://github.com/VaHiX/CodeForces/