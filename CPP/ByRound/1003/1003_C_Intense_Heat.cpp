// Problem: CF 1003 C - Intense Heat
// https://codeforces.com/contest/1003/problem/C

#include <cstdio>
#include <vector>
// Flowerbox: 
// Purpose: This code computes the maximum average temperature over all segments of at least k consecutive days.
// Algorithm: Brute-force approach where for each starting day p, we extend the segment to the right until we reach at least k days,
//            calculating the average at each valid segment and keeping track of the maximum.
// Time Complexity: O(n^2), where n is the number of days. For each starting point p, we iterate up to n times to extend the segment.
// Space Complexity: O(n), due to storing the temperature values in a vector.
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<double> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%lf", &a[p]);
  }
  double mx(0);
  for (long p = 0; p < n; p++) {
    double s(0);
    for (long u = p; u < n; u++) {
      s += a[u]; // Add current day's temperature to the running sum.
      if (u - p + 1 >= k) { // Only consider segments with at least k days.
        double avg = s / (u - p + 1); // Compute the average of the current segment.
        mx = (mx > avg) ? mx : avg; // Update the maximum average if current is greater.
      }
    }
  }
  printf("%.7lf\n", mx);
  return 0;
}

// https://github.com/VaHiX/CodeForces/