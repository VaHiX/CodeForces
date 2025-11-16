// Problem: CF 853 B - Jury Meeting
// https://codeforces.com/contest/853/problem/B

/*
 * Problem: Jury Meeting
 * 
 * Purpose: Find the minimum cost to gather all jury members in Metropolis (city 0) 
 *          for k consecutive days, and then send them back to their respective cities.
 *          Each jury member lives in a city from 1 to n.
 * 
 * Approach:
 * 1. Process flights to determine:
 *    - Flights going to Metropolis (city 0): record departure city and cost
 *    - Flights going from Metropolis: record arrival city and cost
 * 2. For flights to Metropolis:
 *    - Track the minimum cost to reach each city from Metropolis
 *    - Keep prefix minimum cost to reach all cities by some day
 * 3. For flights from Metropolis:
 *    - For each such flight, find the earliest day it can depart such that 
 *      there are k consecutive days available for work.
 *    - Use binary search to find this earliest day and combine with prefix cost.
 * 
 * Time Complexity: O(m * log m)
 * Space Complexity: O(m)
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define N 200010
using namespace std;
int n, m, k, i, x, y, h[N], t;
long long ans, Ans, g[N], f[N];
struct mjj {
  int x, y, z;
} a[N];

// Compare flights by departure day
bool cmp(mjj a, mjj b) { return a.x < b.x; }

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &a[i].x, &x, &y, &a[i].z);
    // If the flight is to Metropolis (city 0), store arrival city
    if (x == 0)
      a[i].y = y;
    else
      // If the flight is from Metropolis (city 0), store negation of departure city
      a[i].y = -x;
  }
  
  Ans = 0;
  Ans = 1e18; // Initialize answer to large number
  sort(a + 1, a + m + 1, cmp); // Sort flights by departure day
  
  // Copy day information for binary search
  for (i = 1; i <= m; i++)
    h[i] = a[i].x;
  
  // Initialize cost tracking for each city
  for (i = 1; i <= n; i++)
    f[i] = 1e12, ans += f[i];
  
  g[0] = 1e18; // Initialize prefix costs array
  
  // Forward pass: track minimum cost to reach all cities
  for (i = 1; i <= m; i++)
    if (a[i].y < 0) { // Flight to Metropolis
      // Update the minimum cost to reach this city
      ans -= f[-a[i].y];
      f[-a[i].y] = min(f[-a[i].y], 1ll * a[i].z);
      ans += f[-a[i].y];
      g[i] = ans; // Store prefix minimum cost to reach all cities
    } else
      g[i] = g[i - 1]; // No change if flight leaving Metropolis
  
  // Reset arrays for backward pass
  memset(f, 63, sizeof(f));
  ans = 0;
  for (i = 1; i <= n; i++)
    f[i] = 1e12, ans += f[i];
  
  // Backward pass: process flights leaving Metropolis
  for (i = m; i >= 1; i--)
    if (a[i].y > 0) { // Flight from Metropolis
      // Update minimum cost to travel from this city
      ans -= f[a[i].y];
      f[a[i].y] = min(f[a[i].y], 1ll * a[i].z);
      ans += f[a[i].y];
      
      // Find the earliest day that allows k consecutive days
      // for work after this flight
      t = lower_bound(h + 1, h + m + 1, a[i].x - k) - h - 1;
      
      // If there exists a valid start day, update answer
      if (t)
        Ans = min(Ans, ans + g[t]);
    }
  
  // Output result
  if (Ans >= 1e12)
    puts("-1"); // Impossible case
  else
    printf("%I64d\n", Ans);
}


// https://github.com/VaHiX/CodeForces/