// Problem: CF 851 B - Arpa and an exam about geometry
// https://codeforces.com/contest/851/problem/B

/*
 * Problem: Arpa and an exam about geometry
 * 
 * Task: Determine if there exists a point and an angle such that rotating the page around the point 
 *       maps point 'a' to 'b', and 'b' to 'c'. This is equivalent to checking if vectors (a->b) and (b->c) 
 *       are equal in length and at a 90-degree angle (clockwise or counterclockwise).
 * 
 * Approach:
 *   - First, check if the distances between consecutive points are equal (i.e., |ab| == |bc|).
 *   - Then, check if the vectors (ab) and (bc) are perpendicular by computing their dot product.
 *     For perpendicular vectors, the dot product should be 0.
 * 
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only using a fixed number of variables.
 */

#include <cstdio>
int main() {
  long long ax, ay, bx, by, cx, cy;
  scanf("%lld %lld %lld %lld %lld %lld", &ax, &ay, &bx, &by, &cx, &cy);
  bool possible = true;
  
  // Check if distances |ab| and |bc| are equal
  if ((bx - ax) * (bx - ax) + (by - ay) * (by - ay) !=
      (cx - bx) * (cx - bx) + (cy - by) * (cy - by)) {
    possible = false;
  }
  
  // Check if vectors ab and bc are perpendicular (dot product equals 0)
  // Dot product = (bx - ax)*(cx - bx) + (by - ay)*(cy - by)
  // For perpendicular vectors, this should be 0
  // Also check if one vector is a 180-degree rotation of the other (which would not satisfy the rotation condition)
  if (((bx - ax) * (cy - ay) == (cx - ax) * (by - ay)) ||
      ((bx - ax) * (cy - ay) == -(cx - ax) * (by - ay))) {
    possible = false;
  }
  
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/