// Problem: CF 1680 D - Dog Walking
// https://codeforces.com/contest/1680/problem/D

/*
Algorithm: Dynamic Programming + Two Pointers + Optimization
Approach:
- The problem involves finding the maximum number of distinct integer points a dog can visit,
  given that some movements are unknown (represented by 0) and can be filled with values in [-k, k].
- The dog must return to point 0 after n minutes.
- For each possible way to fill the zeros, we want to maximize the number of distinct points visited.
- We use prefix sums to calculate cumulative positions and track how many zeros are present.
- For each segment [i, j], we determine the optimal fillings of zeros in that segment and remaining part
  such that the final position is 0, and compute maximum distinct points.

Time Complexity: O(n^2)
Space Complexity: O(n)
*/
#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>

using namespace std;
long long n, m, a, b[3003], s[3003], ans = -1, S, B, rS, rB;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m; // Read n (minutes) and k (max speed)
  for (int i = 1; i <= n; i++)
    cin >> a, b[i] = b[i - 1] + (a == 0), s[i] = s[i - 1] + a; // b[i] counts zeros up to i, s[i] is cumulative sum
  
  // If the fixed part of the walk cannot be balanced by allowing zero parts to be filled within k range, return -1
  if (abs(s[n]) > m * b[n])
    return cout << "-1", 0;
  
  // Try all segments [i, j] and determine best way to assign values to zeros in that segment
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++) {
      S = s[j] - s[i - 1]; // Sum of fixed movements in segment [i,j]
      B = b[j] - b[i - 1]; // Count of zeros in segment [i,j]
      rS = s[n] - S; // Sum of remaining part after segment [i,j]
      rB = b[n] - B; // Count of zeros in remaining part after segment [i,j]
      
      // Determine best way to fill zeros in both parts to maximize distinct points
      // For first part: try +m*B or -m*B, similar for remaining part
      ans = max({ans, min(abs(S + m * B), abs(rS - m * rB)), // Case 1: first part goes max right, second part goes max left
                 min(abs(S - m * B), abs(rS + m * rB))}); // Case 2: first part goes max left, second part goes max right
    }
  // Add 1 because point 0 is always visited
  cout << ans + 1;
  return 0;
}


// https://github.com/VaHiX/CodeForces/