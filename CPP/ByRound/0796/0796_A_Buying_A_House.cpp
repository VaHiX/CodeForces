// Problem: CF 796 A - Buying A House
// https://codeforces.com/contest/796/problem/A

/*
 * Purpose: This program finds the minimum distance from a girl's house to the closest affordable house
 *          that Zane can buy with his budget. Houses are arranged in a line with 10 meters between adjacent ones.
 *
 * Approach:
 *   - Read input values: number of houses (n), girl's house (m), and Zane's money (k)
 *   - For each house:
 *     - If the house is occupied (a[i] == 0) or too expensive (a[i] > k), skip it
 *     - Otherwise, compute the distance from the girl's house to this house
 *     - Keep track of the minimum distance found
 *   - Output the minimum distance multiplied by 10 (since each step is 10 meters)
 *
 * Time Complexity: O(n) - We iterate through all houses once
 * Space Complexity: O(1) - Only a few variables are used regardless of input size
 */
#include <cstdio>
int main() {
  const int D = 10;
  long n, m, k;
  scanf("%ld %ld %ld\n", &n, &m, &k);
  long minDist(n);  // Initialize with maximum possible distance
  for (long p = 1; p <= n; p++) {
    long a;
    scanf("%ld", &a);
    if (a <= 0 || a > k) {
      continue;  // Skip occupied or expensive houses
    }
    long dist = (p > m) ? (p - m) : (m - p);  // Calculate distance between houses
    minDist = (minDist < dist) ? minDist : dist;  // Update minimum distance
  }
  printf("%ld\n", D * minDist);
  return 0;
}


// https://github.com/VaHiX/CodeForces/