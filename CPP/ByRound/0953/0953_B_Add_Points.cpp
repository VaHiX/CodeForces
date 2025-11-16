// Problem: CF 953 B - Add Points
// https://codeforces.com/contest/953/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>
/*
------------------------------------------------------------
Code Purpose:
This program determines the minimum number of points to add to a line so that 
the distances between all neighboring points become equal. It uses the GCD 
algorithm to find the smallest common distance, then calculates how many points 
need to be inserted between each pair of existing points.

Algorithms/Techniques:
- Sorting the points to get them in order
- Computing GCD of all distances to find the minimal step size
- Counting the number of points to insert between each pair

Time Complexity: O(n log n + n log(max_distance))
Space Complexity: O(n)
------------------------------------------------------------
*/
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> x(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &x[p]); // Read each point coordinate
  }
  sort(x.begin(), x.end()); // Sort the points to process in order
  long g = x[1] - x[0]; // Initialize GCD with the first distance
  for (long p = 1; p < n; p++) {
    g = gcd(g, x[p] - x[p - 1]); // Compute GCD of all distances
  }
  long cnt(0);
  for (long p = 1; p < n; p++) {
    cnt += (x[p] - x[p - 1]) / g - 1; // Count points to insert between pairs
  }
  printf("%ld\n", cnt);
  return 0;
}

// https://github.com/VaHiX/CodeForces/