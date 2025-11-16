// Problem: CF 884 C - Bertown Subway
// https://codeforces.com/contest/884/problem/C

/*
 * Code Purpose: This program computes the maximum possible "convenience" 
 * of a subway system in Bertown, after changing at most two subway station 
 * destinations to maximize the number of ordered pairs (x, y) such that one 
 * can travel from station x to station y using the subway.
 *
 * Approach:
 * 1. The subway system is represented as a permutation of stations where each 
 *    station points to exactly one other station (and vice versa).
 * 2. Each such structure forms cycles (or loops).
 * 3. The convenience is the total number of ordered pairs (x, y) such that 
 *    there is a path from x to y. This equals the sum over all cycles of 
 *    the square of the cycle length (because from any node in a cycle of length k, 
 *    there are k paths to k nodes).
 * 4. To maximize convenience, we may change at most two values in the permutation.
 *    Thus, we consider merging two cycles or adding a new path to increase the total.
 * 5. The result is computed by considering the optimal merging strategy:
 *    - If there's one cycle, the result is the square of its length.
 *    - If there are multiple cycles, merge the two largest into one and compute 
 *      the sum of squares of the new set of cycle lengths.
 *
 * Time Complexity: O(n log n) due to sorting the cycle lengths.
 * Space Complexity: O(n) for storing visited flags and cycle lengths.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> dest(n + 1);
  for (ll p = 1; p <= n; p++) {
    scanf("%lld", &dest[p]);
  }
  std::vector<bool> visited(n + 1, 0);
  std::vector<ll> vl;
  for (ll p = 1; p <= n; p++) {
    if (visited[p]) {
      continue;
    }
    ll length(0), cur(p);
    while (!visited[cur]) {
      visited[cur] = true;
      ++length;
      cur = dest[cur];
    }
    vl.push_back(length);
  }
  if (vl.size() <= 1) {
    printf("%lld\n", vl[0] * vl[0]);
  } else {
    sort(vl.begin(), vl.end());
    ll x = vl.back();
    vl.pop_back();
    ll y = vl.back();
    vl.pop_back();
    ll conv = (x + y) * (x + y);
    for (ll p = 0; p < vl.size(); p++) {
      conv += vl[p] * vl[p];
    }
    printf("%lld\n", conv);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/