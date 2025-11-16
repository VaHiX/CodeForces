// Problem: CF 699 A - Launch of Collider
// https://codeforces.com/contest/699/problem/A

/*
 * Problem: Launch of Collider
 * 
 * Purpose: Find the first moment when any two particles collide in a collider.
 *          Each particle moves either left ('L') or right ('R') at 1 m/microsecond speed.
 *          Particles are initially at even integer coordinates.
 * 
 * Approach:
 * - Iterate through particles from left to right.
 * - Keep track of the last particle moving to the right ('R').
 * - When we encounter a particle moving to the left ('L'), we check if it's closer to the 
 *   last 'R' particle than any previous pair.
 * - The collision time between two particles moving towards each other is half the distance between them.
 * 
 * Time Complexity: O(n) - single pass through particles
 * Space Complexity: O(1) - only using a few variables regardless of input size
 * 
 * Algorithms/Techniques: 
 * - Linear scan with state tracking (last right-moving particle)
 * - Collision detection for opposing directions
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string direction;
  std::cin >> direction;
  long minDist(-1);        // Minimum distance between R and L particles that will collide
  long lastRight(-1);      // Coordinate of the last R-moving particle seen
  for (long p = 0; p < n; p++) {
    int to = direction[p] == 'R' ? 1 : -1;  // Direction: 1 for R, -1 for L
    long x;
    std::cin >> x;
    if (to > 0) {
      // If moving right, update the last right-moving particle
      lastRight = x;
    } else if (lastRight >= 0 && (minDist < 0 || (x - lastRight < minDist))) {
      // If moving left and we've seen a right-moving particle before,
      // check if this pair has the smallest distance so far
      minDist = x - lastRight;
    }
  }
  // The time of collision is half the minimum distance (since both move at 1 m/us towards each other)
  long minTime = (minDist < 0) ? (-1) : (minDist / 2);
  std::cout << minTime << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/