// Problem: CF 686 A - Free Ice Cream
// https://codeforces.com/contest/686/problem/A

/*
 * Problem: Free Ice Cream
 * 
 * Purpose: Simulate a queue of people (carriers bringing ice cream or children taking ice cream) 
 *          and calculate the final number of ice cream packs and the number of distressed children.
 * 
 * Algorithms/Techniques:
 *   - Simulation: Process each person in the queue one by one.
 *   - Greedy: Give ice cream to children only if enough packs are available.
 * 
 * Time Complexity: O(n), where n is the number of people in the queue.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <iostream>
int main() {
  long long n, x;
  std::cin >> n >> x;
  long long distress(0);  // Track the number of distressed children
  while (n--) {
    char sgn;
    long long d;
    std::cin >> sgn >> d;
    if (sgn == '+') {
      x += d;  // Add ice cream packs from a carrier
    } else if (sgn == '-' && d > x) {
      ++distress;  // Child cannot get ice cream, increment distress counter
    } else if (sgn == '-' && d <= x) {
      x -= d;  // Give ice cream to child, reduce pack count
    }
  }
  std::cout << x << " " << distress << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/