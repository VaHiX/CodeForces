// Problem: CF 1846 C - Rudolf and the Another Competition
// https://codeforces.com/contest/1846/problem/C

/*
C. Rudolf and the Another Competition
Algorithm: Greedy + Sorting
Time Complexity: O(n * m * log(m)) per test case due to sorting for each participant
Space Complexity: O(m) per test case for storing problem times

The task is to determine Rudolf's final rank in a programming competition where:
- Each participant solves problems in an optimal order.
- Points = number of solved problems.
- Penalty = total time spent solving problems.
- Ranking prioritizes points first, then penalty (lower is better).
- Rudolf is participant 1.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m, h;
    scanf("%lld %lld %lld", &n, &m, &h);
    std::vector<ll> v(m);
    for (ll p = 0; p < m; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort problem times for optimal order (greedy: shortest first)
    ll ct(0), ms(0), mp(0);   // ct: cumulative time, ms: max solved problems, mp: total penalty
    for (ll p = 0; p < m; p++) {
      ct += v[p];             // Add current problem time to cumulative time
      if (ct > h) {           // If we can't solve this problem within time limit
        break;
      }
      ++ms;                   // Increment number of solved problems
      mp += ct;               // Add the time taken to penalty
    }
    ll ans(1);                // Rudolf starts at rank 1
    
    // Process remaining participants (from index 2 onwards)
    for (ll idx = 1; idx < n; idx++) {
      for (ll p = 0; p < m; p++) {
        scanf("%lld", &v[p]);
      }
      sort(v.begin(), v.end());  // Sort their problem times optimally
      
      ct = 0;
      ll cnt(0), penalty(0);
      for (ll p = 0; p < m; p++) {
        ct += v[p];
        if (ct > h) {            // If this problem cannot be solved in time
          break;
        }
        ++cnt;                   // Increment solved count
        penalty += ct;           // Add time to penalty
      }
      
      // Compare results with Rudolf:
      // If less problems solved -> lower rank (continue)
      // If more problems solved -> better rank (+1)
      // If same number of solved problems, compare penalties
      if (cnt < ms) {
        continue;
      } else if (cnt > ms) {
        ++ans;
      } else if (cnt == ms) {
        ans += (penalty < mp);  // If penalty is smaller, increase rank
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/