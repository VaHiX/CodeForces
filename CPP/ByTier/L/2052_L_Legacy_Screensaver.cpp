// Problem: CF 2052 L - Legacy Screensaver
// https://codeforces.com/contest/2052/problem/L

/*
 * Problem: Legacy Screensaver
 * Purpose: Calculate the limit of the fraction of time two rectangles overlap as time approaches infinity.
 * Algorithms/Techniques:
 *   - Simulation of movement with reflection at boundaries.
 *   - Period detection for periodic motion of each rectangle.
 *   - Counting overlapping intervals using GCD-based cycle analysis.
 * Time Complexity: O(W + H) per test case, where W and H are screen dimensions.
 * Space Complexity: O(W + H) per test case, for storing match positions and counts.
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, pii> pos;
template <typename T> bool inset(set<T> &s, T &v) {
  return s.find(v) != s.end();
}
long long gcd(long long a, long long b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int rectsz[2];
    cin >> rectsz[0] >> rectsz[1];
    int sz[2][2], start[2][2], dmove[2][2];
    for (int i = 0; i < 2; i++) {
      cin >> sz[0][i] >> sz[1][i] >> start[0][i] >> start[1][i] >>
          dmove[0][i] >> dmove[1][i];
    }
    vector<int> matches[2]; // Stores time steps when each rectangle is in overlap
    int cs[2];
    for (int i = 0; i < 2; i++) {
      pii poses[2];
      for (int j = 0; j < 2; j++) {
        poses[j] = {start[i][j], dmove[i][j]};
      }
      pos currpos = {poses[0], poses[1]};
      pos startpos = currpos;
      cs[i] = 0;
      while (cs[i] == 0 || startpos != currpos) {
        // Check if rectangles overlap at current step
        if ((poses[0].first >= poses[1].first &&
             poses[0].first < poses[1].first + sz[i][1]) ||
            (poses[1].first >= poses[0].first &&
             poses[1].first < poses[0].first + sz[i][0])) {
          matches[i].push_back(cs[i]);
        }
        for (int j = 0; j < 2; j++) {
          poses[j].first += poses[j].second;
          // Reflection off edges
          if (poses[j].first == 0) {
            poses[j].second *= -1;
          }
          if (poses[j].first + sz[i][j] == rectsz[i]) {
            poses[j].second *= -1;
          }
        }
        cs[i]++;
        currpos = {poses[0], poses[1]};
      }
    }
    int g = gcd(cs[0], cs[1]); // Compute GCD of periods
    vector<long long> vals[2];
    vals[0].assign(g, 0);
    vals[1].assign(g, 0);
    for (int i = 0; i < 2; i++) {
      for (int x : matches[i]) {
        vals[i][x % g]++; // Count overlaps modulo period
      }
    }
    long long ans = 0;
    for (int i = 0; i < g; i++) {
      ans += vals[0][i] * vals[1][i]; // Accumulate total overlaps
    }
    long long lcm = cs[0] / g;
    lcm *= cs[1]; // LCM of both periods
    long long g2 = gcd(ans, lcm); // Reduce the fraction
    ans /= g2;
    lcm /= g2;
    cout << ans << "/" << lcm << endl;
  }
}


// https://github.com/VaHiX/codeForces/