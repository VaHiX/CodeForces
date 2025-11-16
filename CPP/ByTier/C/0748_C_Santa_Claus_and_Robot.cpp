// Problem: CF 748 C - Santa Claus and Robot
// https://codeforces.com/contest/748/problem/C

/*
 * Problem: Santa Claus and Robot
 * Algorithm: Greedy Simulation
 * 
 * The task is to find the minimum number of points in a sequence that could produce
 * a given movement protocol. The key insight is that the robot moves between points
 * along shortest paths (Manhattan distance), and we need to minimize the number of
 * distinct points visited.
 *
 * Approach:
 * - Traverse the movement string.
 * - Keep track of whether we have moved in each of the four directions (L, R, U, D).
 * - When a movement in a direction that "contradicts" a previous movement (e.g. we've moved left and now move right),
 *   we increment the count of points and reset the direction flags.
 * - Similarly for up/down movements.
 *
 * Time Complexity: O(n), where n is the length of the movement string.
 * Space Complexity: O(1), only using a few boolean flags and counters.
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  bool fl(0), fr(0), fu(0), fd(0);  // Flags to track if we've moved in each direction
  long count(1);  // Start with one point (initial position)
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == 'L') {
      fl = 1;
      if (fr) {  // If we have moved right before, this is a new point
        ++count;
        fr = fu = fd = 0;  // Reset all other direction flags
      }
    } else if (s[p] == 'R') {
      fr = 1;
      if (fl) {  // If we have moved left before, this is a new point
        ++count;
        fl = fu = fd = 0;  // Reset all other direction flags
      }
    } else if (s[p] == 'U') {
      fu = 1;
      if (fd) {  // If we have moved down before, this is a new point
        ++count;
        fl = fr = fd = 0;  // Reset all other direction flags
      }
    } else if (s[p] == 'D') {
      fd = 1;
      if (fu) {  // If we have moved up before, this is a new point
        ++count;
        fl = fr = fu = 0;  // Reset all other direction flags
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/