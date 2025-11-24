// Problem: CF 888 B - Buggy Robot
// https://codeforces.com/contest/888/problem/B

/*
 * Problem: B. Buggy Robot
 * 
 * Purpose: 
 *   Determine the maximum number of commands from a sequence that can be executed 
 *   such that the robot ends up at the starting position (0, 0). Some commands 
 *   may have been ignored, and we want to find the maximum valid commands that 
 *   could lead back to the origin.
 * 
 * Algorithm:
 *   1. Count occurrences of each direction: L, R, U, D.
 *   2. To return to (0, 0), the number of L and R commands must balance, 
 *      and the number of U and D commands must balance.
 *   3. For horizontal movement (L and R): we can use min(left, right) pairs.
 *   4. For vertical movement (U and D): we can use min(up, down) pairs.
 *   5. Total moves = 2 * (min(L,R) + min(U,D)) because each pair contributes 
 *      2 commands to the total count.
 * 
 * Time Complexity: O(n) where n is the length of the command string.
 * Space Complexity: O(1) as we only use a fixed amount of extra space.
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long left(0), right(0), up(0), down(0);
  for (long p = 0; p < n; p++) {
    if (s[p] == 'L') {
      ++left;
    } else if (s[p] == 'R') {
      ++right;
    } else if (s[p] == 'U') {
      ++up;
    } else if (s[p] == 'D') {
      ++down;
    }
  }
  // Calculate maximum valid commands that can bring robot back to origin
  long count = 2 * (left < right ? left : right) + 2 * (up < down ? up : down);
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/