// Problem: CF 1807 F - Bouncy Ball
// https://codeforces.com/contest/1807/problem/F

/* 
 * Problem: Bouncy Ball
 * 
 * Algorithm/Techniques: Simulation with direction tracking and wall bouncing.
 * 
 * Time Complexity: O(n * m) per test case in worst case, due to simulation of ball movement until it reaches target or cycles.
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 * 
 * The ball moves in a grid of size n x m, starting from (i1, j1) in direction d.
 * It bounces off walls by flipping direction along the axis of the wall.
 * The simulation continues until the ball reaches (i2, j2) or enters a cycle (not reaching target).
 * 
 * Key aspects:
 * - The ball maintains direction until it hits a wall.
 * - When hitting a wall, direction flips accordingly.
 * - The process is simulated with max steps limited to 2 * n * m to avoid infinite loops.
 * - Corner bounces involve flipping both directions.
 * 
 * Input:
 *   n, m: grid dimensions.
 *   x, y: starting position.
 *   a, b: target position.
 *   d: initial direction ('DR', 'DL', 'UR', 'UL').
 * 
 * Output:
 *   Number of bounces until reaching (a, b), or -1 if never reached.
 */

#include <iostream>
#include <string>

#define ll long long
using namespace std;
int n, m;
int x, y; // current position of the ball
int a, b; // target position
string dir; // current direction
int ans = 0; // bounce counter

// Check if the current position is a corner (both x and y are at edges)
bool isCorner() {
  bool ret = true;
  ret &= ((x == 1) || (x == n)); // x is at top or bottom edge
  ret &= ((y == 1) || (y == m)); // y is at left or right edge
  return ret;
}

// Update direction upon hitting a wall
void checkDir() {
  bool q = false; // flag to indicate if a bounce occurred
  
  // If moving up and at top edge, flip direction down
  if (dir[0] == 'U' && x == 1) {
    dir[0] = 'D';
    q = true;
  }
  
  // If moving down and at bottom edge, flip direction up
  if (dir[0] == 'D' && x == n) {
    dir[0] = 'U';
    q = true;
  }
  
  // If moving left and at left edge, flip direction right
  if (dir[1] == 'L' && y == 1) {
    dir[1] = 'R';
    q = true;
  }
  
  // If moving right and at right edge, flip direction left
  if (dir[1] == 'R' && y == m) {
    dir[1] = 'L';
    q = true;
  }
  
  ans += (int)q; // add bounce count
}

// Main solution logic for one test case
void solution() {
  cin >> n >> m >> x >> y >> a >> b >> dir;
  bool q = false; // flag to indicate if reached target
  ans = 0; // reset bounce counter
  int temp = n * m * 2; // max steps to prevent infinite loop
  
  while (temp--) {
    // Check if reached the target
    if ((x == a) && (y == b)) {
      q = true;
      break;
    }
    
    checkDir(); // process wall collision
    
    // Update position based on direction
    if (dir[0] == 'U')
      x--; // move up
    else
      x++; // move down
    
    if (dir[1] == 'L')
      y--; // move left
    else
      y++; // move right
  }
  
  // Output result
  if (q)
    cout << ans << '\n';
  else
    cout << "-1\n";
}

// Entry point
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solution();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/