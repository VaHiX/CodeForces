// Problem: CF 1292 A - NEKO's Maze Game
// https://codeforces.com/contest/1292/problem/A

#include <cstdio>
#include <vector>
int main() {
  long n, q;
  scanf("%ld %ld", &n, &q);
  // 2D vector to represent the maze grid, with 2 rows and n columns
  std::vector<std::vector<bool>> s(2, std::vector<bool>(n, 0));
  long cnt(0);  // Counter for the number of blocked connections between rows
  while (q--) {
    long row, col;
    scanf("%ld %ld", &row, &col);
    --row;  // Convert to 0-based indexing
    --col;
    
    if (s[row][col]) {  // If cell was previously active (ground)
      // Decrement counter when removing a connection that was blocking path
      if (s[1 - row][col]) {
        --cnt;  // Adjacent cell in other row is now blocked, reduce count
      }
      if (col > 0 && s[1 - row][col - 1]) {
        --cnt;  // Left neighbor in other row is blocked, reduce count
      }
      if (col + 1 < n && s[1 - row][col + 1]) {
        --cnt;  // Right neighbor in other row is blocked, reduce count
      }
    } else {  // If cell was previously inactive (lava)
      // Increment counter when adding a connection that blocks path
      if (s[1 - row][col]) {
        ++cnt;  // Adjacent cell in other row is now unblocked, increase count
      }
      if (col > 0 && s[1 - row][col - 1]) {
        ++cnt;  // Left neighbor in other row is unblocked, increase count
      }
      if (col + 1 < n && s[1 - row][col + 1]) {
        ++cnt;  // Right neighbor in other row is unblocked, increase count
      }
    }
    s[row][col] = 1 - s[row][col];  // Toggle state of current cell
    puts(cnt <= 0 ? "Yes" : "No");  // Output result based on connection count
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/