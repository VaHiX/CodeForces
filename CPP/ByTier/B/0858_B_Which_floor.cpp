// Problem: CF 858 B - Which floor?
// https://codeforces.com/contest/858/problem/B

#include <cstdio>
// Purpose: Determine the floor of a given flat number based on known flat-floor mappings.
// Algorithm: 
//   - For each known flat-floor pair, compute the minimum possible flats per floor (left)
//     and maximum possible flats per floor (right) that are consistent with the data.
//   - Then, use these bounds to determine how many flats are on the nth floor.
//   - If both bounds give the same floor, return that floor; otherwise return -1.
// Time Complexity: O(m), where m is the number of known flat-floor pairs.
// Space Complexity: O(1), only using a few integer variables.

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int left(1), right(1000);  // left: min flats per floor, right: max flats per floor
  while (m--) {
    int x, f;
    scanf("%d %d", &x, &f);
    // Compute the minimum number of flats per floor based on this flat-floor pair
    int l = (x / f) + (x % f > 0);
    left = (left > l) ? left : l;  // update lower bound
    --f;
    --x;
    if (f <= 0) {
      continue;
    }
    // Compute the maximum number of flats per floor based on this flat-floor pair
    right = (right < (x / f)) ? right : (x / f);  // update upper bound
  }
  // Compute the floor for flat n using the min and max possible flats per floor
  int u = (n / left) + (n % left > 0);
  int v = (n / right) + (n % right > 0);
  printf("%d\n", (u == v) ? u : -1);  // if both computed floors are equal, return it, else -1
  return 0;
}


// https://github.com/VaHiX/CodeForces/