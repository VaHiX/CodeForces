// Problem: CF 1782 A - Parallel Projection
// https://codeforces.com/contest/1782/problem/A

/*
 * Problem: Minimum cable length between laptop and projector in a rectangular room
 * 
 * Algorithms/Techniques:
 * - Parallel Projection (manhattan distance on unfolded 2D surface)
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * The problem is to find the shortest path from point (a,b) on the floor to point (f,g) on the ceiling,
 * where the cable can only travel along walls, floor or ceiling, and must be parallel to room edges.
 * 
 * Key idea:
 * Since the cable path must stay on surfaces, we can "unfold" the room into a 2D plane
 * by considering different ways the cable can go around the cuboid:
 * - Over the floor and ceiling
 * - Around walls to reach from one surface to another
 * 
 * We compute several possible paths:
 * 1. Direct vertical distance + path along floor and ceiling (a, b) -> (f, g)
 * 2. Path going through left wall: (a,b) -> (0,b) -> (0,0) -> (w,0) -> (w,g) -> (f,g)
 * 3. Path going through right wall: (a,b) -> (w,b) -> (w,0) -> (0,0) -> (0,g) -> (f,g)
 * 4. Path going through front wall: (a,b) -> (a,0) -> (0,0) -> (0,d) -> (d,g) -> (f,g)
 * 5. Path going through back wall: (a,b) -> (a,d) -> (w,d) -> (w,0) -> (0,0) -> (f,g)
 * 
 * The solution computes all possibilities and returns the minimum.
 */

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int t, w, d, h, a, b, f, g;

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d%d%d%d", &w, &d, &h, &a, &b, &f, &g);
    printf("%d\n",
           h + min(a + f + abs(b - g), // Path: from (a,b) to (0,0) and then directly to (f,g)
                   min(b + g + abs(a - f), // Path: from (a,b) along x-axis to (w, d) then to (f, g)
                       min(w - a + w - f + abs(b - g), // Path: through front wall
                           d - b + d - g + abs(a - f))))); // Path: through side walls
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/