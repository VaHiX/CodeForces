// Problem: CF 492 B - Vanya and Lanterns
// https://codeforces.com/contest/492/problem/B

/*
B. Vanya and Lanterns
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing lantern positions

Vanya walks late at night along a straight street of length l, 
lit by n lanterns. Each lantern lights all points within distance d.
We need to find the minimum d such that the entire street [0, l] is lit.

Approach:
1. Sort the lantern positions.
2. Check the gap between consecutive lanterns and also the gaps from start (0) and end (l).
3. For each gap, compute the required d to cover it - this will be half the gap size.
4. Return maximum of all such computed d values.
*/

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  long n, l;
  scanf("%ld %ld\n", &n, &l);
  std::vector<long> lanterns(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &lanterns[p]);
  }
  sort(lanterns.begin(), lanterns.end());
  
  // Initialize d with the distance from start (0) to first lantern
  double d = l - lanterns[n - 1];
  
  // If the first lantern doesn't cover the start, adjust d
  if (lanterns[0] > d) {
    d = lanterns[0];
  }
  
  // Check gaps between consecutive lanterns
  for (long p = 1; p < lanterns.size(); p++) {
    // If gap is larger than current d * 2, we need to increase d
    if (lanterns[p] - lanterns[p - 1] > 2 * d) {
      d = 0.5 * (lanterns[p] - lanterns[p - 1]);
    }
  }
  
  printf("%.10lf\n", d);
  return 0;
}


// https://github.com/VaHiX/codeForces/