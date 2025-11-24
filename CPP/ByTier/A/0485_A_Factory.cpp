// Problem: CF 485 A - Factory
// https://codeforces.com/contest/485/problem/A

/*
 * Code Purpose:
 * This program determines whether the mythical detail production process will eventually stop.
 * The process works as follows: if there are x details at the start of a day, then (x % m) new
 * details are produced at the end of that day. All produced details stay in storage.
 * The goal is to detect if the number of details ever becomes divisible by m, which would
 * cause the production to stop.
 *
 * Algorithm:
 * - Start with initial number of details 'a'
 * - Simulate the daily production using the formula: a = (2 * a) % m
 * - Keep track of all previously seen values in a set to detect cycles
 * - If we see a value that was already seen, a cycle is detected, and production does not stop → "No"
 * - If at any point a becomes 0, production stops → "Yes"
 *
 * Time Complexity: O(m), because in the worst case, we can have at most m distinct remainders
 * Space Complexity: O(m), due to the set storing up to m different values
 */

#include <cstdio>
#include <set>
int main() {
  long a, m;
  scanf("%ld %ld", &a, &m);
  std::set<long> rem; // Set to store previously seen remainders
  rem.insert(a);
  bool forever = 0; // Flag indicating if production goes forever (stops at 0)
  while (true) {
    a = (2 * a) % m;  // Update a to next day's count: 2*a % m
    if (a == 0) {
      forever = 0;  // Production stops when a becomes 0
      break;
    } else if (a > 0 && rem.find(a) == rem.end()) {
      rem.insert(a);  // Add new remainder to set
    } else {
      forever = 1;  // A cycle is detected, so production does not stop
      break;
    }
  }
  puts(forever ? "No" : "Yes");  // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/