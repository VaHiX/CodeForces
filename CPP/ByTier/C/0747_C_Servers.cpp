// Problem: CF 747 C - Servers
// https://codeforces.com/contest/747/problem/C

/*
 * Problem: C. Servers
 * Purpose: Determine which tasks can be performed based on server availability.
 * Algorithm: 
 *   - Use a map to track when each server becomes free (timer[i] stores the free time).
 *   - For each task, check if there are enough unoccupied servers.
 *   - Assign the k smallest-id servers to the task if possible.
 *   - Update server availability after assignment.
 * 
 * Time Complexity: O(q * n) where q is number of tasks and n is number of servers.
 * Space Complexity: O(n) for storing server availability times.
 */

#include <iostream>
#include <map>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j;
  ll n, q, c = 0;
  ll unc, count, ct;
  cin >> n >> q;
  ll t[q], d[q], k[q];
  for (i = 0; i < q; i++)
    cin >> t[i] >> k[i] >> d[i];
  unc = n;
  ct = 0;
  map<ll, ll> timer;  // Map to store when each server becomes free
  for (i = 1; i <= n; i++)
    timer[i] = 0;  // Initially all servers are free at time 0
  for (i = 0; i < q; i++) {
    ct = t[i];
    c = 0, count = 0;
    // Free up servers that become available at or before current task start time
    for (j = 1; j <= n; j++) {
      if (timer[j] <= ct && timer[j] != 0) {
        timer[j] = 0;
        unc++;
      }
    }
    // Check if enough servers available
    if (k[i] > unc) {
      cout << "-1" << endl;
    } else {
      // Assign k smallest id servers to the task
      for (j = 1; j <= n; j++) {
        if (timer[j] == 0 && k[i] > 0) {
          timer[j] = ct + d[i];  // Mark server as busy until ct+d[i]
          unc--;
          count += j;  // Add server id to result
          k[i]--;
        }
      }
      cout << count << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/