// Problem: CF 883 A - Automatic Door
// https://codeforces.com/contest/883/problem/A

/*
 * Problem: Automatic Door
 * 
 * Algorithm/Techniques: 
 *   - Simulation with two pointers to track employees and clients.
 *   - Use of binary search (upper_bound) to efficiently skip clients that enter during door open time.
 *   - Math-based calculation to determine how many employees can enter within a period.
 * 
 * Time Complexity: O(m * log(m) + n * log(n)) where m is number of clients and n is number of employees.
 *   - Sorting clients takes O(m * log(m)).
 *   - The main while loop runs in O(n + m) since each pointer only advances.
 *   - Each binary search operation is O(log(m)).
 * Space Complexity: O(m) for storing client times.
 * 
 * Description:
 *   - Simulates an automatic door that opens when people arrive and closes after d seconds.
 *   - Handles overlapping arrival times and ensures all people can enter before door closes.
 *   - Counts how many times the door opens based on arrival schedule of employees and clients.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
typedef long long LL;
const LL inf = 3e18;

// Helper function to update minimum value
void gmin(LL &x, LL y) {
  if (y < x)
    x = y;
}

LL t[N]; // Array to store client arrival times
LL n, A, m, D; // n: number of employees, A: step size for employee arrivals, m: number of clients, D: door closing delay

int main() {
  while (~scanf("%lld%lld%lld%lld", &n, &m, &A, &D)) {
    // Read client arrival times
    for (int i = 1; i <= m; ++i)
      scanf("%lld", &t[i]);
    
    // Sort client times and remove duplicates
    sort(t + 1, t + m + 1);
    m = unique(t + 1, t + m + 1) - t - 1;
    
    // Add a large value to end of array to avoid bounds checking
    t[m + 1] = inf;
    
    // Pointers for employees and clients
    LL p1 = 1, p2 = 1;
    
    // Calculate how many employee arrivals happen within one door closing interval
    LL num_in_D = D / A + 1;
    
    // Count total door openings
    LL ans = 0;
    
    // Main simulation loop
    while (p1 <= n || p2 <= m) {
      LL now = inf; // Current time when the next door opens
      
      // Get next arrival time either from employee or client
      if (p1 <= n)
        gmin(now, p1 * A);
      if (p2 <= m)
        gmin(now, t[p2]);
      
      // Time when door will close after opening at 'now'
      LL can = now + D;
      
      // If client arrives exactly at the same time door opens
      if (p2 <= m && t[p2] == now) {
        ++ans; // Door opens once
        // Move employee pointer to next unprocessed employee
        p1 = can / A + 1;
        // Move client pointer beyond the time until door closes
        p2 = upper_bound(t + p2, t + m + 1, can) - t;
        continue;
      }
      
      // Move client pointer to the first client that would arrive after door closes
      p2 = upper_bound(t + p2, t + m + 1, can) - t;
      
      // Determine last possible employee that can enter before door closes
      LL ED = t[p2] - D - 1;
      LL lastp1 = min(ED / A, n);
      
      // Calculate how many employees can enter during this window
      LL add = (lastp1 - p1 + 1 + num_in_D - 1) / num_in_D;
      ans += add;
      
      // Advance employee pointer
      p1 += add * num_in_D;
    }
    
    // Output result
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/