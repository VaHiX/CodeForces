// Problem: CF 1196 C - Robot Breakout
// https://codeforces.com/contest/1196/problem/C

/*
Algorithm: 
The problem is about finding a point that all robots can reach. Each robot has 4 possible moves (up, down, left, right) and a subset of these may be disabled. 
The approach is to determine the region of points that can be reached by all robots by analyzing which moves are possible for each robot.

For movement to be possible, a robot can use one of the 4 directions:
1. Move down (y decrease): enabled if f[i][0] = 1
2. Move right (x increase): enabled if f[i][1] = 1
3. Move up (y increase): enabled if f[i][2] = 1
4. Move left (x decrease): enabled if f[i][3] = 1

For each robot, we can determine:
- If the robot cannot move left, it means it can't reach points with x < current_x
- If the robot cannot move right, it means it can't reach points with x > current_x
- If the robot cannot move up, it means it can't reach points with y > current_y
- If the robot cannot move down, it means it can't reach points with y < current_y

Thus, the intersection of all such constraints gives a rectangle where all robots can meet.

This is done by:
1. Initialize boundaries: xmin = -1e5, xmax = 1e5, ymin = -1e5, ymax = 1e5
2. For each robot, adjust the boundaries based on which moves are disabled:
   - If robot cannot move down, x coordinate must be >= current x (i.e., xmin = max(xmin, x))
   - If robot cannot move up, x coordinate must be <= current x (i.e., xmax = min(xmax, x))
   - If robot cannot move left, y coordinate must be >= current y (i.e., ymin = max(ymin, y))
   - If robot cannot move right, y coordinate must be <= current y (i.e., ymax = min(ymax, y))
3. After processing all robots, check if there's a valid intersection of regions (xmax >= xmin && ymax >= ymin)
   - If intersection is valid, output the center of the rectangle
   - Otherwise, output "0"

Time Complexity: O(n) per query
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    long xmin(-1e5), xmax(1e5), ymin(-1e5), ymax(1e5);
    for (long p = 0; p < n; p++) {
      long x, y, down, right, up, left;
      scanf("%ld %ld %ld %ld %ld %ld", &x, &y, &down, &right, &up, &left);
      if (!down) {
        xmin = (xmin > x) ? xmin : x;   // If robot cannot go down, all reachable points must have x >= current x
      }
      if (!up) {
        xmax = (xmax < x) ? xmax : x;   // If robot cannot go up, all reachable points must have x <= current x
      }
      if (!left) {
        ymin = (ymin > y) ? ymin : y;   // If robot cannot go left, all reachable points must have y >= current y
      }
      if (!right) {
        ymax = (ymax < y) ? ymax : y;   // If robot cannot go right, all reachable points must have y <= current y
      }
    }
    if ((xmax < xmin) || (ymax < ymin)) {
      puts("0");   // No intersection - impossible to meet
    } else {
      printf("1 %ld %ld\n", (xmin + xmax) / 2, (ymin + ymax) / 2); // Output a point in the intersection
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/