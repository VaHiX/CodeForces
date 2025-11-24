// Problem: CF 730 G - Car Repair Shop
// https://codeforces.com/contest/730/problem/G

/*
G. Car Repair Shop

Purpose:
This code schedules car repair requests in a single-car shop according to specific rules.
Each request has a preferred start day and duration. The scheduler attempts to schedule
the request at its preferred time if that slot is free. If not, it finds the earliest
available consecutive time window of required duration.

Algorithms/Techniques:
- Greedy scheduling with interval conflict checking
- Linear search through previously scheduled intervals for each new request

Time Complexity: O(n^3) where n is the number of requests.
Space Complexity: O(n) for storing the schedule of events.

Input Format:
- First line contains integer n (number of requests)
- Followed by n lines, each containing two integers s_i and d_i (start day and duration)

Output Format:
- For each request, print the start and end day of its scheduled repair.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> start(n + 1, 0), finish(n + 1, 0); // Store start and end times for each request
  for (ll p = 1; p <= n; p++) {
    ll s, d;
    scanf("%lld %lld", &s, &d);
    ll a(s), b(s + d - 1); // a = start of preferred interval, b = end of preferred interval
    bool free(true);
    // Check if preferred interval is free from previous requests
    for (ll u = 0; u < p; u++) {
      if (!((b < start[u]) || (finish[u] < a))) { // If intervals overlap
        free = false;
        break;
      }
    }
    if (free) {
      start[p] = s;
      finish[p] = b;
      continue;
    }
    // If preferred interval is not free, look for the earliest available slot
    for (ll t = 0; t < p; t++) {
      a = finish[t] + 1; // Start from just after previous interval
      b = a + d - 1;
      free = true;
      // Check if this new interval conflicts with any existing intervals
      for (ll u = 0; u < p; u++) {
        if (!((b < start[u]) || (finish[u] < a))) { // If intervals overlap
          free = false;
          break;
        }
      }
      if (!free) {
        continue; // Not a valid slot, try next one
      } else if ((start[p] == 0) || (a < start[p])) { // Update if this is earlier than current best
        start[p] = a;
        finish[p] = b;
      }
    }
  }
  for (ll p = 1; p <= n; p++) {
    printf("%lld %lld\n", start[p], finish[p]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/