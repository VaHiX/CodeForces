// Problem: CF 1623 A - Robot Cleaner
// https://codeforces.com/contest/1623/problem/A

/*
Problem: Robot Cleaner
Algorithm: Simulation with reflection
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem models a robot moving in a grid room with reflections off walls.
The robot starts at (rb, cb) and moves with velocity (dr, dc). When it hits a wall,
it reflects by changing the sign of the corresponding velocity component.

Instead of simulating each step, we compute directly:
- The horizontal distance to the target row (rd), considering reflections
- The vertical distance to the target column (cd), considering reflections
- Return the minimum of these two distances

The approach works because:
1. The robot moves in a periodic pattern due to reflections
2. We can compute how many steps it takes to reach the target row or column
3. The answer is the minimum of both times
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, rb, cb, rd, cd;
    scanf("%ld %ld %ld %ld %ld %ld", &n, &m, &rb, &cb, &rd, &cd);
    
    // Compute horizontal steps to reach target row
    // If rb <= rd, move directly; otherwise reflect the movement
    long x = (rb <= rd) ? (rd - rb) : (2 * n - rb - rd);
    
    // Compute vertical steps to reach target column
    // If cb <= cd, move directly; otherwise reflect the movement  
    long y = (cb <= cd) ? (cd - cb) : (2 * m - cb - cd);
    
    // Output minimum of horizontal and vertical step counts
    printf("%ld\n", (x < y) ? x : y);
  }
}


// https://github.com/VaHiX/codeForces/