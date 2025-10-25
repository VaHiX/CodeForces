// Problem: CF 1283 E - New Year Parties
// https://codeforces.com/contest/1283/problem/E

/*
E. New Year Parties
Algorithms/Techniques: Greedy approach with frequency counting and simulation
Time Complexity: O(N) where N = 2e5 + 20
Space Complexity: O(N) for the frequency array f

The problem involves placing n friends on a number line such that each friend can move to one of three positions: left neighbor, current position, or right neighbor.
We need to find the minimum and maximum number of distinct occupied houses after all moves.

Approach:
1. For minimum: Greedily place friends to minimize overlaps. If we have a friend at position i, try to avoid placing another friend in adjacent positions unless necessary.
2. For maximum: Distribute friends as far apart as possible to maximize unique occupied positions.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 20;
int n, a[N], f[N], pv, mn, mx;

int main() {
  scanf("%d", &n); // Read number of friends
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]), f[a[i]]++; // Count frequency of each position
  
  // Calculate minimum occupied houses
  // Greedily select non-overlapping groups of 3 consecutive positions
  for (int i = 1; i < N; i++) {
    if (f[i] == 0) continue; // Skip empty positions
    mn++; // Count this group
    i += 2; // Skip next two positions to avoid overlap
  }
  
  // Calculate maximum occupied houses
  // Distribute friends such that they don't cluster together
  for (int i = 1; i < N; i++) {
    if (f[i] == 0) continue; // Skip empty positions
    // If left neighbor is unoccupied, occupy it to avoid overuse of current position
    if (f[i - 1] == 0)
      f[i - 1]++, f[i]--;
    // If current position has more than one friend and right exists, move one friend there
    if (f[i] > 1 and i + 1 < N)
      f[i + 1]++, f[i]--;
  }
  
  // Count final number of occupied houses for maximum case
  for (int i = 0; i < N; i++)
    if (f[i] > 0)
      mx++;
  
  printf("%d %d", mn, mx); // Output min and max occupied houses
}


// https://github.com/VaHiX/codeForces/