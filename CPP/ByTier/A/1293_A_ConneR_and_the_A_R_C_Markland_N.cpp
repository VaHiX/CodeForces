// Problem: CF 1293 A - ConneR and the A.R.C. Markland-N
// https://codeforces.com/contest/1293/problem/A

/*
 * Problem: A. ConneR and the A.R.C. Markland-N
 *
 * Purpose: Determine the minimum number of staircases ConneR needs to walk
 *          from his current floor 's' to reach the closest open restaurant.
 *
 * Algorithm:
 *   - For each test case, we maintain a set of closed floors.
 *   - Starting from floor 's', we search outward in both directions (up and down).
 *   - For each step distance p from 's', check if either s+p or s-p is an open restaurant.
 *   - Return the first valid step count where such a restaurant exists.
 *
 * Time Complexity: O(k + n) per test case, where k is the number of closed restaurants
 *                  and n is the number of floors. In worst case (k = n-1), this is O(n).
 *                  However, since k <= 1000 and sum of k over all test cases <= 1000,
 *                  amortized performance is acceptable.
 *
 * Space Complexity: O(k) for storing the set of closed floors.
 */

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s, k;
    scanf("%ld %ld %ld", &n, &s, &k);
    std::set<long> d; // Set to store closed restaurant floors
    for (long p = 0; p < k; p++) {
      long x;
      scanf("%ld", &x);
      d.insert(x); // Insert each closed floor into the set
    }
    long dist(0); // Variable to store minimum distance
    for (long p = 0; p < n; p++) {
      // Check if moving up from s (s + p) leads to an open restaurant
      if (s + p <= n && d.count(s + p) == 0) {
        dist = p;
        break;
      }
      // Check if moving down from s (s - p) leads to an open restaurant
      if (s - p > 0 && d.count(s - p) == 0) {
        dist = p;
        break;
      }
    }
    printf("%ld\n", dist);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/