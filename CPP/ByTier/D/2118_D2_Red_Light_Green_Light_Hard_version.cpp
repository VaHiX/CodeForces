// Problem: CF 2118 D2 - Red Light, Green Light (Hard version)
// https://codeforces.com/contest/2118/problem/D2

/*
 * Problem: D2. Red Light, Green Light (Hard version)
 *
 * Purpose:
 *   Given a strip of length 10^15 with n traffic lights at positions p[i],
 *   each having an initial delay d[i], determine if starting at position pos
 *   and moving in a direction, you will eventually leave the strip within 10^100 seconds.
 *
 * Algorithm:
 *   - For each light, precompute sets of positions based on modulo classes.
 *   - Simulate movement using memoization and cycle detection to avoid infinite loops.
 *   - Use binary search (upper/lower bounds) to efficiently find next position.
 *
 * Time Complexity: O((n + q) * log(n)) per test case
 * Space Complexity: O(n * k) in worst case for storage of sets and maps.
 */

#include <bits/std_abs.h>
#include <iostream>
#include <map>
#include <set>
#include <utility>

using namespace std;

long long n, k;
// dp stores computed results for (pos, dir) -> whether player escapes
map<pair<long long, bool>, bool> dp;
// vt tracks visited states to detect cycles
map<pair<long long, bool>, bool> vt;
// zr marks positions where traffic light is red at time 0
map<long long, bool> zr;
// rt and lt store positions grouped by their modulo (time difference) for forward/backward movement
map<long long, set<long long>> rt, lt;

/**
 * Find next position based on direction and current time
 */
long long fnd(long long pos, bool dir, long long time) {
  if (dir) { // Moving forward
    const auto &st = rt[((time - pos) % k + k) % k];
    auto it = st.upper_bound(pos);
    if (it == st.end())
      return -1; // No next position to the right
    return *it;
  } else { // Moving backward
    const auto &st = lt[(time + pos) % k];
    auto it = st.lower_bound(pos);
    if (it == st.begin())
      return -1; // No previous position to the left
    --it;
    return *it;
  }
}

/**
 * Recursive solve to determine if escape is possible from current state
 */
bool solve(long long pos, bool dir, long long time) {
  long long next = fnd(pos, dir, time);
  if (next == -1)
    return dp[{next, dir}] = 1; // Escaped the strip

  dir = !dir; // Turn around when hitting a red light
  if (dp.count({next, dir}))
    return dp[{next, dir}]; // Already computed result

  if (vt.count({next, dir}))
    return dp[{next, dir}] = 0; // Detected cycle, not escaping

  vt[{next, dir}] = 1; // Mark as visited
  return dp[{next, dir}] = solve(next, dir, time + abs(pos - next)); // Recursive call
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    rt.clear(), lt.clear(), dp.clear(), zr.clear();
    cin >> n >> k;
    long long p[n], d[n];
    for (int i = 0; i < n; i++)
      cin >> p[i];
    for (int i = 0; i < n; i++) {
      cin >> d[i];
      if (d[i] == 0)
        zr[p[i]] = 1;
    }
    for (int i = 0; i < n; i++) {
      rt[(((d[i] - p[i]) % k) + k) % k].insert(p[i]); // Grouping by mod for forward search
      lt[(d[i] + p[i]) % k].insert(p[i]); // Grouping by mod for backward search
    }
    int q;
    cin >> q;
    while (q--) {
      long long pos;
      cin >> pos;
      vt.clear();
      bool dir = 1; // Start direction: forward
      if (zr[pos])
        dir = 0; // If this position has red light at time 0, face backwards
      bool ans = solve(pos, dir, 0);
      cout << (ans ? "YES" : "NO") << '\n';
    }
  }
}


// https://github.com/VaHiX/CodeForces/