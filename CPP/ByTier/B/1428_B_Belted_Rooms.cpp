// Problem: CF 1428 B - Belted Rooms
// https://codeforces.com/contest/1428/problem/B

/*
B. Belted Rooms
Algorithm: 
  - For each room, we check if it's possible to leave and come back.
  - A room is returnable if there exists a path from that room back to itself.
  - We analyze the conveyor belt directions:
    * '<' means ant-clockwise connection (i+1) -> i
    * '>' means clockwise connection i -> (i+1)
    * '-' means bidirectional connection
  - Key observation: If all belts are directed in one way (all '<' or all '>'), then all rooms are returnable.
  - Otherwise, a room is returnable if it has at least one adjacent belt that allows movement towards it,
    or if it's connected to an off belt (-).

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (excluding input)
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool left(true), right(true); // Flags to check if there are '>', '<' in the string
    long cnt(0);
    for (long p = 0; p < n; p++) {
      // Check if either previous or current position has '-' which allows bidirectional movement
      if ((s[(n + p - 1) % n] == '-') || (s[p % n] == '-')) {
        ++cnt;
      }
      // If we find a '<' direction, it means there is no exit to the left of this belt
      if (s[p] == '<') {
        right = false;
      } else if (s[p] == '>') {
        // If we find a '>' direction, it means there is no exit to the right of this belt
        left = false;
      }
    }
    // If all belts are either clockwise or anticlockwise, then all rooms are returnable
    if (left || right) {
      cnt = n;
    }
    std::cout << cnt << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/