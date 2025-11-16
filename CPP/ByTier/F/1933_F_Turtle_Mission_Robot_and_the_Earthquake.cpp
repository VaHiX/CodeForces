// Problem: CF 1933 F - Turtle Mission: Robot and the Earthquake
// https://codeforces.com/contest/1933/problem/F

/*
Algorithm: BFS with time-aware state tracking
Approach: 
- Use BFS to explore all possible paths from (0,0) to (n-1,m-1)
- State representation: (x,y) coordinates are packed into a single integer
- The grid is cyclic in the vertical direction, so we need to track the movement of rocks over time
- BFS is performed with time tracking, and we check for valid moves at each time step
- Optimization: use two queues for bidirectional BFS, and a packed coordinate system for efficient memory usage

Time Complexity: O(n * m * (n + m))
Space Complexity: O(n * m)

Key techniques:
1. Bit manipulation for packed coordinates: x and y are combined into one integer
2. Two queue BFS to reduce time complexity
3. In-place rock state updating to avoid extra memory
*/
#include <iostream>
#include <vector>
#include <algorithm>

const int shift = 10;
const int mask = (1 << shift) - 1;
int n, m;
inline int X(int xy) { return xy & mask; } // Extract x coordinate from packed integer
inline int Y(int xy) { return xy >> shift; } // Extract y coordinate from packed integer
inline int xy(int x, int y) { return (y << shift) + (x % n); } // Pack x,y coordinates into integer
char a[1 << 2 * shift]; // Grid state storage using packed coordinates
std::vector<int> q[2]; // Two queues for BFS with alternating usage
void proc() {
  std::cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      std::cin >> a[xy(i, j)]; // Read in the grid
  q[0].clear();
  q[1].clear();
  q[0].push_back(xy(0, 0)); // Start from (0,0)
  a[xy(0, 0)] = '2'; // Mark as visited
  const int mx = 1'000'000'000;
  int r = mx; // Result variable to store minimum time
  for (int t = 0; t < r && q[t % 2].size(); t++) { // BFS with time tracking
    for (auto v : q[t % 2]) {
      int x = X(v), y = Y(v); // Unpack current state
      if (y == m - 1) // If at the destination column
        r = std::min(r, ((x + n) - (n - 1 + t) % n) % n + t); // Calculate time to reach destination
      // Right move: check if next cell is safe and not occupied
      if (y < m - 1 && a[xy(x + 1, y + 1)] == '0') {
        q[1 - t % 2].push_back(xy(x + 1, y + 1)); // Add to next queue
        a[xy(x + 1, y + 1)] = '2'; // Mark as visited
      }
      // Down move: check if next cell is safe and not occupied by falling rock
      if (a[xy(x + 1, y)] != '1' && a[xy(x + 2, y)] == '0') {
        q[1 - t % 2].push_back(xy(x + 2, y)); // Add to next queue
        a[xy(x + 2, y)] = '2'; // Mark as visited
      }
    }
    q[t % 2].clear(); // Clear current queue for next iteration
  }
  std::cout << (r == mx ? -1 : r) << std::endl; // Output result or -1 if impossible
}
int main() {
  q[0].reserve(1'000'000); // Pre-allocate memory for queues
  q[1].reserve(1'000'000);
  std::cin.tie(0);
  std::cin.sync_with_stdio(false);
  std::cout.sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--)
    proc();
  return 0;
}


// https://github.com/VaHiX/CodeForces/