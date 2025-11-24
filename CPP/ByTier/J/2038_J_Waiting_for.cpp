// Problem: CF 2038 J - Waiting for...
// https://codeforces.com/contest/2038/problem/J

/*
 * Problem: J. Waiting for...
 * Purpose: Simulate a bus stop scenario where people arrive and buses with limited seats arrive.
 *          For each bus arrival, determine if Monocarp can board the bus (only if there's at least one seat left after others board).
 *
 * Algorithm:
 *   - Maintain a counter 'w' representing current number of people at the bus stop (excluding Monocarp).
 *   - Process events in order:
 *     - For "P p" event: add 'p' people to the stop.
 *     - For "B b" event: 
 *       - Calculate how many people can board (min(w, b)).
 *       - If fewer than 'b' people board, then Monocarp can board (i.e., w < b).
 *       - Output YES if he can board; otherwise NO.
 *       - Update 'w' to reflect only those who didn't get on the bus.
 *
 * Time Complexity: O(n), where n is the number of events. Each operation is constant time.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <iostream>
#include <string>
int main() {
  long w(0);             // Number of people at the bus stop (excluding Monocarp)
  long t;                // Number of events
  std::cin >> t;
  while (t--) {
    std::string s;       // Event type ("B" or "P")
    std::cin >> s;
    long x;              // Number of people or seats
    std::cin >> x;
    if (s == "B") {      // If a bus arrives
      w -= x;            // Remove x people from waiting (this is a simplified model)
      std::cout << (w < 0 ? "YES" : "NO") << std::endl;  // Print YES if Monocarp can board
      w = (w > 0 ? w : 0);  // Ensure w doesn't go negative
    } else {             // If people arrive
      w += x;            // Add them to the waiting list
    }
  }
}


// https://github.com/VaHiX/codeForces/