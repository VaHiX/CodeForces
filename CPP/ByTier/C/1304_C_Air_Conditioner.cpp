// Problem: CF 1304 C - Air Conditioner
// https://codeforces.com/contest/1304/problem/C

/*
 * Problem: C. Air Conditioner
 * Purpose: Determine if it's possible to satisfy all customer temperature preferences 
 *          by controlling an air conditioner with states: off, heating, cooling.
 * Algorithm: 
 *   - For each customer visit, we track the minimum and maximum possible temperatures 
 *     that can be achieved before this customer arrives.
 *   - At each customer visit time t_i:
 *     1. Update mn = mn - (t_i - prev_time) and mx = mx + (t_i - prev_time) to account for 
 *        temperature changes if we keep current state (heating/cooling/off).
 *     2. Adjust mn and mx to respect the constraints defined by the customer's range [l_i, h_i].
 *     3. Check if it's possible to satisfy any temperature in [l_i, h_i], i.e., 
 *        whether there exists a valid interval [mn, mx] intersecting non-empty with [l_i, h_i].
 * 
 * Time Complexity: O(n) per test case (linear scan of customer visits)
 * Space Complexity: O(1) (only using fixed number of variables)
 */


#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    bool possible(true);
    long mn(m), mx(m), prev(0); // mn: min possible temp; mx: max possible temp; prev: last visit time
    for (long p = 0; p < n; p++) {
      long t, d, u;
      scanf("%ld %ld %ld", &t, &d, &u);
      long diff = t - prev; // Time elapsed since last customer
      prev = t; // Update previous visit time
      mn -= diff; // Account for max possible cooling
      mx += diff; // Account for max possible heating
      if (mx < d || mn > u) { // If no valid temperature can satisfy this customer
        possible = false;
      }
      mn = (mn > d) ? mn : d; // Restrict min to meet demand
      mx = (mx < u) ? mx : u; // Restrict max to meet demand
    }
    puts(possible ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/