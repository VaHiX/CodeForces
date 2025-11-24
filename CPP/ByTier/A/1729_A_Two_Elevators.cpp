// Problem: CF 1729 A - Two Elevators
// https://codeforces.com/contest/1729/problem/A

/*
 * Problem: A. Two Elevators
 * Purpose: Determine which elevator reaches floor 1 faster for Vlad to get to his apartment.
 *
 * Algorithms/Techniques:
 *   - Simulation of elevator movement
 *   - Distance calculation using absolute difference
 *   - Comparison of travel times
 *
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1), only constant extra space used
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long first(a - 1);  // Distance for first elevator to reach floor 1
    first = (first >= 0) ? first : -first;  // Absolute value of distance
    long secondA(b - c), secondB(c - 1);  // First part: b->c, second part: c->1
    secondA = (secondA >= 0) ? secondA : -secondA;  // Absolute value of first segment
    secondB = (secondB >= 0) ? secondB : -secondB;  // Absolute value of second segment
    long second = secondA + secondB;  // Total time for second elevator
    if (first < second) {
      puts("1");  // First elevator is faster
    } else if (second < first) {
      puts("2");  // Second elevator is faster
    } else {
      puts("3");  // Both elevators arrive at the same time
    }
  }
}


// https://github.com/VaHiX/codeForces/