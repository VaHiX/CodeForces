// Problem: CF 1974 D - Ingenuity-2
// https://codeforces.com/contest/1974/problem/D

/*
 * Problem: Distribute instructions between rover and helicopter on Mars so that
 * both end up at the same final position.
 *
 * Algorithms/Techniques:
 * - Greedy approach to split movements
 * - Calculate total displacement and check if it can be split equally
 * - Assign each instruction to either rover (R) or helicopter (H) greedily
 *
 * Time Complexity: O(n) per test case, where n is the number of instructions
 * Space Complexity: O(n) for storing the result string and input
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
    long tx(0), ty(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'N') {
        ++ty;
      } else if (s[p] == 'S') {
        --ty;
      } else if (s[p] == 'E') {
        ++tx;
      } else if (s[p] == 'W') {
        --tx;
      }
    }
    // If total displacement is odd in either direction, it's impossible to split equally
    if (tx % 2 || ty % 2) {
      std::cout << "NO" << std::endl;
      ;
      continue;
    }
    // Target half-displacement for each device
    long hx(tx / 2), hy(ty / 2);
    bool rfa(false), rfb(false); // Flags to ensure both devices execute at least one instruction
    long cx(0), cy(0); // Current coordinates for the helicopter
    std::string r(s); // Result string to store 'R' or 'H'
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'N') {
        // If not assigned yet or we're below target y, assign to helicopter
        if (!rfa || cy < hy) {
          ++cy;
          r[p] = 'H';
          rfa = true;
        } else {
          // Otherwise assign to rover
          r[p] = 'R';
          rfb = true;
        }
      } else if (s[p] == 'S') {
        // Similar logic for South movement
        if (!rfa || cy > hy) {
          --cy;
          r[p] = 'H';
          rfa = true;
        } else {
          r[p] = 'R';
          rfb = true;
        }
      } else if (s[p] == 'E') {
        // Similar logic for East movement
        if (!rfa || cx < hx) {
          ++cx;
          r[p] = 'H';
          rfa = true;
        } else {
          r[p] = 'R';
          rfb = true;
        }
      } else if (s[p] == 'W') {
        // Similar logic for West movement
        if (!rfa || cx > hx) {
          --cx;
          r[p] = 'H';
          rfa = true;
        } else {
          r[p] = 'R';
          rfb = true;
        }
      }
    }
    // Check if both devices executed at least one instruction
    if (rfa && rfb) {
      std::cout << r << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/