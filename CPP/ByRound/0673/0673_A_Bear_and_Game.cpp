// Problem: CF 673 A - Bear and Game
// https://codeforces.com/contest/673/problem/A

/*
 * Problem: Bear and Game
 * Algorithm/Technique: Simulation with early termination
 * 
 * Time Complexity: O(n), where n is the number of interesting minutes.
 * Space Complexity: O(1), only using a constant amount of extra space.
 *
 * The solution simulates the game watching process. It checks for 15 consecutive
 * boring minutes and stops early if found. Otherwise, it computes how long
 * the game is watched.
 */

#include <algorithm>
#include <cstdio>
const int D = 90;  // Duration of the game in minutes
const int T = 15;  // Threshold for consecutive boring minutes
int main() {
  int n;
  scanf("%d\n", &n);
  int ans(D);        // Initialize answer to full duration
  int current(0);    // Track the last interesting minute seen
  while (n--) {
    int x;
    scanf("%d", &x);
    // If gap between current and next interesting minute is >= 15,
    // then there are 15 or more consecutive boring minutes
    if (current + T < x) {
      break;  // Stop watching the game
    }
    current = x;  // Update the last seen interesting minute
  }
  // The game is watched until either:
  // 1. The last interesting minute + 15 (i.e., the end of the 15-minute window),
  // 2. Or the full 90 minutes (whichever comes first)
  ans = std::min(current + 15, D);
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/