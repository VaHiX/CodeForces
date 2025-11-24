// Problem: CF 737 A - Road to Cinema
// https://codeforces.com/contest/737/problem/A

/*
 * Problem: Road to Cinema
 * 
 * Purpose: Find the minimum cost of a car that can reach the cinema in time t.
 *          Cars can be driven in normal (1 km/min, 1 liter fuel) or accelerated mode (1 km/min, 2 liters fuel).
 *          There are gas stations along the road where fuel can be refilled for free.
 * 
 * Algorithms/Techniques:
 * - Binary search on car capacity to find minimum cost car that works
 * - Preprocessing to calculate optimal path times for different fuel capacities
 * - Greedy optimization using prefix sums and sorted distances
 * 
 * Time Complexity: O(n * log(max_v) + k * log(k))
 * Space Complexity: O(k + n)
 * 
 * Where n is number of cars, k is number of gas stations, and max_v is maximum fuel tank capacity.
 */

#include <stdio.h>
#include <algorithm>

#define inf 0x3f3f3f3f
#define NN 202020
using namespace std;
using INT = long long;
int c[NN], v[NN], len[NN], dp[NN], m, s, t;
INT sum[NN];

// Function to check if a car with capacity v can reach in time t
bool can(int v) {
  // If the maximum distance a car can cover is less than total road length, impossible
  if (len[m] > v)
    return 0;
  // Find the maximum number of segments that can be covered in accelerated mode
  int id = upper_bound(len + 1, len + m + 1, v >> 1) - len;
  // Calculate time needed to cover remaining segment in normal mode
  return dp[id - 1] + (sum[id] - (INT)v * (m - id + 1)) <= t;
}

int main() {
  int n, k;
  scanf("%d %d %d %d", &n, &k, &s, &t);
  
  // Read car details
  for (int i = 1; i <= n; i++)
    scanf("%d %d", c + i, v + i);
  
  // Initialize starting and ending points
  len[m++] = 0, len[m++] = s;
  
  // Read gas station positions
  while (k--)
    scanf("%d", len + m), m++;
  
  // Sort gas station positions
  sort(len, len + m);
  
  // Convert absolute positions to relative distances
  for (int i = m; --i;)
    len[i] -= len[i - 1];
  
  // Remove first element (0) and sort distances
  m--, sort(len + 1, len + m + 1);
  
  // Precompute prefix sums of segment lengths (used for time calculation)
  for (int i = 1; i <= m; i++)
    dp[i] = dp[i - 1] + len[i];
  
  // Precompute suffix sums to compute time required for optimal driving
  for (int i = m; i; i--)
    sum[i] = sum[i + 1] + 3LL * len[i];
  
  int ans = inf;
  
  // Try all cars to find minimum cost that works
  for (int i = 1; i <= n; i++) {
    if (can(v[i]))
      ans = min(ans, c[i]);
  }
  
  printf("%d", ans < inf ? ans : -1);
}


// https://github.com/VaHiX/CodeForces/