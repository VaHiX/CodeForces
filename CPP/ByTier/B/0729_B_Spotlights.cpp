// Problem: CF 729 B - Spotlights
// https://codeforces.com/contest/729/problem/B

/*
B. Spotlights
Theater stage is a rectangular field of size n × m. The director gave you the stage's plan which actors will follow. For each cell it is stated in the plan if there would be an actor in this cell or not.
You are to place a spotlight on the stage in some good position. The spotlight will project light in one of the four directions (if you look at the stage from above) — left, right, up or down. Thus, the spotlight's position is a cell it is placed to and a direction it shines.
A position is good if two conditions hold: 
there is no actor in the cell the spotlight is placed to; 
there is at least one actor in the direction the spotlight projects.
Count the number of good positions for placing the spotlight. Two positions of spotlight are considered to be different if the location cells or projection direction differ.

Algorithms/Techniques:
- For each row, we compute how many empty cells can see actors to their left and right.
- Similarly, for each column, we compute how many empty cells can see actors above and below.
- This allows us to count valid spotlight positions by checking all four directions from each empty cell.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Input
The first line contains two positive integers n and m (1 ≤ n, m ≤ 1000) — the number of rows and the number of columns in the plan.
The next n lines contain m integers, 0 or 1 each — the description of the plan. Integer 1, means there will be an actor in the corresponding cell, while 0 means the cell will remain empty. It is guaranteed that there is at least one actor in the plan.
Output
Print one integer — the number of good positions for placing the spotlight.
*/
#include <iostream>
#include <vector>
int main() {
  std::ios_base::sync_with_stdio(false);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> s(n, std::vector<int>(m, 0));
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < m; col++) {
      std::cin >> s[row][col];
    }
  }
  long count(0);
  for (int row = 0; row < n; row++) {
    int left(0); // Tracks if any actor is to the left in current row
    for (int col = 0; col < m; col++) {
      if (s[row][col]) {
        left = 1; // Found an actor, update flag
      } else {
        count += left; // Add to count if there's an actor to the left of this empty cell
      }
    }
    int right(0); // Tracks if any actor is to the right in current row
    for (int col = m - 1; col >= 0; col--) {
      if (s[row][col]) {
        right = 1; // Found an actor, update flag
      } else {
        count += right; // Add to count if there's an actor to the right of this empty cell
      }
    }
  }
  for (int col = 0; col < m; col++) {
    int up(0); // Tracks if any actor is above in current column
    for (int row = 0; row < n; row++) {
      if (s[row][col]) {
        up = 1; // Found an actor, update flag
      } else {
        count += up; // Add to count if there's an actor above this empty cell
      }
    }
    int down(0); // Tracks if any actor is below in current column
    for (int row = n - 1; row >= 0; row--) {
      if (s[row][col]) {
        down = 1; // Found an actor, update flag
      } else {
        count += down; // Add to count if there's an actor below this empty cell
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/