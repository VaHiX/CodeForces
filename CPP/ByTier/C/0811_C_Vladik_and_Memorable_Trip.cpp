// Problem: CF 811 C - Vladik and Memorable Trip
// https://codeforces.com/contest/811/problem/C

/*
Code Purpose:
This code solves the problem of maximizing the total comfort of a train trip by optimally partitioning a sequence of people into segments. Each segment's comfort is defined as the XOR of all distinct city codes in that segment. The partition must ensure all people going to the same city are in the same segment.

Approach:
- Preprocessing: For each city code, record the first and last occurrence (lef and rig arrays).
- Dynamic Programming: For each position i, compute the maximum comfort achievable up to that point.
  - For each possible segment ending at i, check if it's valid (i.e., all people going to the same city are included).
  - Update the DP state with the maximum value.

Time Complexity: O(n^2), where n is the number of people.
Space Complexity: O(n), for storing arrays and DP table.

*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 5005;
int dp[N], a[N], lef[N], rig[N];
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (!lef[a[i]])  // Record first occurrence of city code a[i]
      lef[a[i]] = i;
    rig[a[i]] = i;   // Record last occurrence of city code a[i]
  }
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];  // Initialize with previous best value
    int lim = i, cost = 0;  // lim tracks the leftmost boundary of current valid segment, cost tracks XOR of distinct cities
    for (int j = i; j > 0; j--) {
      lim = min(lim, lef[a[j]]);  // Update the leftmost boundary
      if (rig[a[j]] > i)  // If person's city extends beyond current segment end, break
        break;
      if (j == rig[a[j]])  // If this is the last person going to city a[j], include it in XOR
        cost ^= a[j];
      if (j == lim) {  // If we've reached the start of valid segment
        dp[i] = max(dp[i], dp[j - 1] + cost);  // Update DP with new maximum
      }
    }
  }
  cout << dp[n];
}


// https://github.com/VaHiX/CodeForces/