// Problem: CF 903 C - Boxes Packing
// https://codeforces.com/contest/903/problem/C

/*
 * Code Purpose:
 * This program determines the minimum number of visible boxes
 * when packing boxes into each other based on their sizes.
 * 
 * Algorithm:
 * - For each box size, count how many boxes exist of that size.
 * - The maximum count of boxes of any single size corresponds to
 *   the minimum number of visible boxes, since those boxes cannot
 *   be nested within each other.
 * 
 * Time Complexity: O(n * log n) due to map operations (insertion and access)
 * Space Complexity: O(n) for storing the counts in the map
 */

#include <cstdio>
#include <map>
int main() {
  long n;
  scanf("%ld", &n);
  std::map<long, long> m;  // Map to store frequency of each box size
  long mc(0);              // Maximum count of boxes of same size
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++m[x];               // Increment frequency of box size x
    mc = (mc > m[x]) ? mc : m[x];  // Update maximum frequency
  }
  printf("%ld\n", mc);
  return 0;
}


// https://github.com/VaHiX/CodeForces/