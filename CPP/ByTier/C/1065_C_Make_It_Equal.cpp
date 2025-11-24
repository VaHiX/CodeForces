// Problem: CF 1065 C - Make It Equal
// https://codeforces.com/contest/1065/problem/C

/*
C. Make It Equal
Algorithms/Techniques: Frequency counting, prefix sum, greedy

Time Complexity: O(max(h) + n) where max(h) is the maximum tower height (up to 2*10^5)
Space Complexity: O(max(h)) for the frequency array eq

The problem involves making all towers equal in height using "good" slices,
where each slice removes cubes from towers taller than the slice height.
A slice is good if its cost (number of removed cubes) does not exceed k.

We use frequency counting to track how many towers have each height.
Then we process heights in descending order to compute prefix sums,
which helps determine how many cubes need to be removed for a given level.
Finally, we greedily select the minimum number of good slices needed.
*/

#include <cstdio>
const int N = 200000;
int n, k;
int eq[N + 2]; // frequency array to count towers at each height
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    ++eq[v]; // count towers of height v
  }
  // Build prefix sum from top to bottom to know how many towers are at least height i
  for (int i = N; i > 0; --i)
    eq[i - 1] += eq[i];
  
  int t = 0;   // number of slices used
  int s = 0;   // current total cubes removed in ongoing slice group
  for (int i = N; i >= 0 && eq[i] != n; --i) { // loop until all towers are at same height
    if (s + eq[i] > k) { // if adding this level's towers would exceed k, start new slice
      ++t;
      s = 0;
    }
    s += eq[i]; // accumulate current slice cost
  }
  printf("%d\n", t + (bool)s); // add one more slice if there is remaining work
  return 0;
}


// https://github.com/VaHiX/codeForces/