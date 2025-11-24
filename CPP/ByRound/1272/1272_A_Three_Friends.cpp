// Problem: CF 1272 A - Three Friends
// https://codeforces.com/contest/1272/problem/A

/*
 * Problem: Three Friends
 * Algorithm: Greedy approach with sorting and optimal position adjustments
 * Time Complexity: O(1) per test case (sorting 3 elements is constant time)
 * Space Complexity: O(1) (only using a fixed-size vector)
 *
 * Description:
 * Given three positions on a coordinate axis, each friend can move at most once 
 * (left or right by 1 unit). The goal is to minimize the total pairwise distance
 * |a' - b'| + |a' - c'| + |b' - c'| after one minute.
 *
 * Strategy:
 * 1. Sort the initial positions to simplify analysis.
 * 2. Increment the two smallest values if they are less than the largest.
 * 3. Decrement the largest value if it is greater than the smallest.
 * 4. Compute final result as 2 * (largest - smallest).
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    std::vector<long> x(3);           // Vector to hold the three positions
    scanf("%ld %ld %ld", &x[0], &x[1], &x[2]);
    sort(x.begin(), x.end());         // Sort so that x[0] <= x[1] <= x[2]
    if (x[0] < x[2]) {                // If smallest is less than largest
      ++x[0];                         // Move smallest toward largest
    }
    if (x[1] < x[2]) {                // If middle is less than largest
      ++x[1];                         // Move middle toward largest
    }
    if (x[2] > x[0]) {                // If largest is greater than smallest
      --x[2];                         // Move largest toward smallest
    }
    long ans = 2 * (x[2] - x[0]);     // Compute minimum total pairwise distance
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/