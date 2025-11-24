// Problem: CF 1781 A - Parallel Projection
// https://codeforces.com/contest/1781/problem/A

/*
 * Problem: Minimum cable length between laptop and projector in a rectangular room
 * Algorithm: Parallel Projection (Manhattan distance on unfolded 2D surface)
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The problem involves finding the shortest path from point (a,b) on the floor to point (f,g) on the ceiling,
 * where the path must follow walls, floor or ceiling and remain parallel to edges.
 * 
 * By unfolding the 3D space into 2D planes, we can consider all possible paths as straight lines in the 2D space.
 * The four candidate paths correspond to different ways of unfolding the room:
 * 1. From (a,b) to (f, g+h) via floor and wall
 * 2. From (a,b) to (f, g-h) via ceiling and wall  
 * 3. From (a,b) to (f+w, g) via left wall and ceiling
 * 4. From (a,b) to (f-w, g) via right wall and ceiling
 * 
 * We calculate the Manhattan distances for these paths and return the minimum.
 */

#include <cstdio>
long myabs(long x) { return (x > 0 ? x : -x); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long w, d, h;
    scanf("%ld %ld %ld", &w, &d, &h);
    long a, b, f, g;
    scanf("%ld %ld %ld %ld", &a, &b, &f, &g);
    
    // Distance via floor and wall: from (a,b) to (f,g) on floor, then up to ceiling above (f,g)
    long distA = g + myabs(f - a) + b;
    
    // Distance via ceiling and wall: from (a,b) to (f,g) on ceiling, then down to floor below (f,g)  
    long distB = (d - g) + myabs(f - a) + (d - b);
    
    // Distance via left wall and ceiling: from (a,b) to (f+w, g) on right wall, then up to ceiling above (f,g)
    long distC = f + a + myabs(g - b);
    
    // Distance via right wall and ceiling: from (a,b) to (f-w, g) on left wall, then up to ceiling above (f,g)
    long distD = (w - f) + (w - a) + myabs(g - b);
    
    // Find the minimum distance among all four possible paths
    long dist = (distA < distB) ? distA : distB;
    dist = (dist < distC) ? dist : distC;
    dist = (dist < distD) ? dist : distD;
    
    // Add height h to get final cable length
    printf("%ld\n", h + dist);
  }
}


// https://github.com/VaHiX/codeForces/