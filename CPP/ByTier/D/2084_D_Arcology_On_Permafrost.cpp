// Problem: CF 2084 D - Arcology On Permafrost
// https://codeforces.com/contest/2084/problem/D

/*
D. Arcology On Permafrost
Algorithms/Techniques: Greedy construction with modular arithmetic
Time Complexity: O(n) per test case
Space Complexity: O(n) for output array

The problem asks to construct a sequence of length n such that after at most m operations,
each operation removing a subarray of length k, the minimum excluded value (MEX) of the 
remaining sequence is maximized. 

Key insight:
- To maximize MEX, we want to avoid having all values from 0 to some x present in the final array.
- We distribute values cyclically such that no segment of length k contains all values from 0 to max_val.
- If m * k < n, then it's always possible to ensure that at least (n / (m + 1)) distinct values appear 
  in a way such that after removing up to m segments we still maintain a large MEX.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int t, n, m, k;
void solve() {
  scanf("%d%d%d", &n, &m, &k);
  int x = max(n / (m + 1), k); // Determine number of distinct values needed
  for (int i = 0; i < n; i++)
    cout << i % x << " "; // Distribute values cyclically modulo x
  cout << "\n";
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/