// Problem: CF 534 B - Covered Path
// https://codeforces.com/contest/534/problem/B

/*
B. Covered Path
Algorithm: Greedy approach to maximize the total path length by choosing optimal speeds at each second.
Time Complexity: O(t) - single loop over t seconds.
Space Complexity: O(t) - two vectors of size t for storing speed arrays.

The problem asks to find the maximum possible length of a road segment given:
- Initial speed v1 and final speed v2
- Time t (number of seconds)
- Maximum allowed speed change d per second

We use a greedy strategy by constructing two sequences:
- sa: increasing sequence from vs to vf with maximum allowed increments
- sb: decreasing sequence from vf to vs with maximum allowed decrements

Then, we take the minimum of corresponding elements from sa and sb at each second,
which ensures that the path length is maximized under constraints.
*/

#include <cstdio>
#include <vector>
int main() {
  long v1, v2;
  scanf("%ld %ld\n", &v1, &v2);
  long t, d;
  scanf("%ld %ld\n", &t, &d);
  long vs = v1;
  long vf = v2;
  if (v1 > v2) {
    vs = v2;
    vf = v1;
  }
  std::vector<long> sa(t, 0); // Store increasing speed sequence
  std::vector<long> sb(t, 0); // Store decreasing speed sequence
  long ans(0);
  for (long p = 0; p < t; p++) {
    sa[p] = vs + p * d;                    // Build increasing speed array
    sb[t - 1 - p] = vf + p * d;            // Build decreasing speed array
  }
  for (long p = 0; p < t; p++) {
    ans += (sa[p] < sb[p]) ? sa[p] : sb[p]; // Take min to maximize total distance
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/