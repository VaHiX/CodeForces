// Problem: CF 812 B - Sagheer, the Hausmeister
// https://codeforces.com/contest/812/problem/B

/*
 * Problem: B. Sagheer, the Hausmeister
 *
 * Purpose: Find the minimum time to turn off all lights in a building with n floors and m rooms per floor.
 *          Sagheer starts at the left stairs on the ground floor and must turn off all lights in order,
 *          going floor by floor, and can only go upstairs after finishing a floor.
 *
 * Algorithm: Dynamic Programming with States
 *            For each floor, we track the minimum cost to reach the left and right staircases in two ways:
 *            left[p] = minimum time to reach left stair on floor p
 *            right[p] = minimum time to reach right stair on floor p
 *
 * Time Complexity: O(n * m)
 * Space Complexity: O(n * m) due to storing the building structure and DP arrays
 *
 * Techniques:
 *   1. Dynamic Programming with two states (left and right staircases)
 *   2. Preprocessing to find the last floor with any light on
 *   3. Efficient computation of movement costs between floors and within floors
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::vector<std::string> a(n + 1);
  for (long p = 0; p < n; p++) {
    std::cin >> a[n - 1 - p]; // Read floors from bottom to top
  }
  long last(n - 1);
  // Find the last floor that has any light on
  for (long p = n - 1; p >= 0; p--) {
    last = p;
    long on(0);
    for (long u = 0; u < a[p].size(); u++) {
      on += (a[p][u] == '1');
    }
    if (on) {
      break;
    }
  }
  // DP arrays to store minimum cost to reach left and right stair on each floor
  std::vector<long> left(n, 0), right(n, 0);
  for (long p = 0; p <= last; p++) {
    long leftLight(m + 1), rightLight(0);
    // Find leftmost room with light on on the current floor
    for (long u = 1; u < a[p].size(); u++) {
      if (a[p][u] == '1') {
        leftLight = u;
        break;
      }
    }
    // Find rightmost room with light on on the current floor
    for (long u = m; u > 0; u--) {
      if (a[p][u] == '1') {
        rightLight = u;
        break;
      }
    }
    if (p == 0) {
      // On ground floor, need to go to rightmost room to turn off lights
      left[p] = (2 - (last == p)) * rightLight;
      right[p] = m + 1; // Just to mark that we don't need to come back
      continue;
    } else if (p == last) {
      // Last floor case: calculate cost to go from previous stair to current stair,
      // turning off lights in between
      left[p] = left[p - 1] + 1 + rightLight;
      right[p] = right[p - 1] + 1 + (m + 1 - leftLight);
    } else {
      // General case: evaluate all transition paths between left and right staircases
      long leftToLeft = left[p - 1] + 1 + 2 * rightLight; // Go from left to right, then to left
      long leftToRight = left[p - 1] + 1 + (m + 1);       // Go from left to right
      long rightToLeft = right[p - 1] + 1 + (m + 1);      // Go from right to left
      long rightToRight = right[p - 1] + 1 + 2 * (m + 1 - leftLight); // Go from right to left, then to right
      left[p] = (leftToLeft < rightToLeft) ? leftToLeft : rightToLeft;
      right[p] = (leftToRight < rightToRight) ? leftToRight : rightToRight;
    }
  }
  // Return minimum of reaching left or right stair on last floor
  long total = (left[last] < right[last]) ? left[last] : right[last];
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/