// Problem: CF 1810 D - Climbing the Tree
// https://codeforces.com/contest/1810/problem/D

/*
 * Code Purpose: 
 *   This code solves the problem of determining whether a snail's climbing time 
 *   (in days) is consistent with a known tree height and whether we can deduce 
 *   the number of days a snail will take to climb a tree based on previously 
 *   accepted information.
 *   
 *   Key algorithm:
 *   - For event type 1 (claiming n days), we calculate the range of possible heights
 *     that would allow a snail with attributes (a,b) to finish climbing in exactly n days.
 *     This is done using the formula for snail movement: 
 *     - On day 1: climbs 'a' meters, but slides back 'b' meters
 *     - From day 2 to n: climbs 'a' meters during day, slides 'b' meters during night
 *     - On final day (n-th), if at least 'a' meters remain, it finishes without sliding
 *   - We keep track of the valid range of heights [l, r] as new valid claims are added.
 *   - For event type 2 (querying days), we calculate the possible range of finishing 
 *     days for the snail based on current [l, r], and if only one value is possible, 
 *     output that; otherwise, output -1.
 *   
 *   Time Complexity: O(q) where q is the number of events, as each event is processed in O(1).
 *   Space Complexity: O(q) for storing the answers.
 */
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int N = 1000010;

void solve() {
  int m;
  scanf("%d", &m);
  LL l = 0, r = 0; // l and r represent the range of valid tree heights
  int op, a, b, n;
  vector<LL> ans;
  while (m--) {
    scanf("%d", &op);
    if (op == 1) {
      // Process a snail claiming to have finished in n days
      scanf("%d%d%d", &a, &b, &n);
      LL mi, mx;
      if (n == 1) {
        // If only one day, snail climbs 'a' meters in a day and cannot slide back
        mi = 1, mx = a;
      } else {
        // Compute min and max heights possible for this snail to finish on the nth day
        // Min height: snail climbs a meters on 1st day, but still has to slide (n-2)(a-b) meters
        // and climbs 'a' more, but finishes on last day, so total is (n-2)(a-b) + a + 1
        mi = (LL)(n - 2) * (a - b) + a + 1;
        // Max height: snail climbs (n-1)(a-b) + a meters but can slide back b meters
        mx = (LL)(n - 1) * (a - b) + a;
      }
      if (l == 0) {
        // First claim, initialize interval
        l = mi, r = mx;
        ans.push_back(1);
      } else {
        // Check if interval overlaps, if it does, update to intersection
        if (mx < l || mi > r) {
          ans.push_back(0); // Contradicting claim
        } else {
          ans.push_back(1); // Valid claim
          l = max(l, mi);
          r = min(r, mx);
        }
      }
    } else {
      // Process a query
      scanf("%d%d", &a, &b);
      if (l == 0) {
        ans.push_back(-1); // No valid interval known yet
        continue;
      }
      // Calculate min and max possible days needed for snail with (a,b) to finish
      // t1: min days based on minimum allowed height
      LL t1 = (LL)(l - a + a - b - 1) / (a - b) + 1;
      // t2: max days based on maximum allowed height
      LL t2 = (LL)(r - a + a - b - 1) / (a - b) + 1;
      t1 = max(t1, 1ll); // At least 1 day
      t2 = max(t2, 1ll);
      if (t1 == t2) {
        ans.push_back(t1); // Unique answer
      } else {
        ans.push_back(-1); // Indeterminate
      }
    }
  }
  for (auto t : ans) {
    printf("%lld ", t);
  }
  puts("");
}

int main() {
  int _ = 1;
  scanf("%d", &_);
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/