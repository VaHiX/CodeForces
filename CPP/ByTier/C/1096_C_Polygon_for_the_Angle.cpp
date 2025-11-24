// Problem: CF 1096 C - Polygon for the Angle
// https://codeforces.com/contest/1096/problem/C

/*
 * C. Polygon for the Angle
 *
 * Problem Description:
 * Given an angle 'ang', find the smallest regular n-gon such that there exist three vertices 
 * a, b, c (not necessarily consecutive) where angle abc = ang. If no such n exists, return -1.
 *
 * Approach:
 * For a regular n-gon inscribed in a circle, each vertex subtends an angle of 360/n at the center.
 * Any angle formed by three vertices can be expressed as k * (360/n) / 2 where k is the number 
 * of steps between two points on the polygon (considering the smallest arc).
 * This leads us to express the angle in terms of n and some integer k.
 * The minimal valid n exists when:
 *   - ang = (k * 180) / n for some integer k
 *   - Rearranging: k = (ang * n) / 180
 *   - Since we want minimal n, we iterate to find the smallest valid n.
 *   - If k + 1 == n, then it's a special case where the angle is formed by two adjacent 
 *     arcs and requires doubling of n.
 *
 * Time Complexity: O(log(max(180, ang)) * T), due to gcd computation per query,
 *                  with the number of queries being at most 180.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long ang;
    scanf("%ld", &ang);
    long g = gcd(ang, 180);                // Compute GCD of angle and 180
    long k = ang / g;                      // Normalize the angle to k/180
    long n = 180 / g;                      // Initial candidate for number of vertices
    
    if (k + 1 == n) {                      // Special case adjustment
      n *= 2;
    }
    printf("%ld\n", n);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/