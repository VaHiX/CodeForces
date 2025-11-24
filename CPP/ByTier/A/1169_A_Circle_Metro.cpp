// Problem: CF 1169 A - Circle Metro
// https://codeforces.com/contest/1169/problem/A

#include <iostream>
using namespace std;
int n, a, x, b, y;
int main() {
  cin >> n >> a >> x >> b >> y;
  // Simulate the movement of both toads on their respective routes
  while (a != x && b != y) {
    // Move Daniel's train forward (route 1: 1->2->...->n->1->...)
    a++;
    if (a == n + 1)
      a = 1;
    // Move Vlad's train backward (route 2: n->(n-1)->...->1->n->...)
    b--;
    if (b == 0)
      b = n;
    // Check if they meet at the same station
    if (a == b)
      return cout << "YES", 0;
  }
  // If loop ends without meeting, they never meet
  return cout << "NO", 0;
}
/*
Flowerbox:
Problem: Determine if two toads on a circular subway system will ever be at the same station at the same time.
Algorithms/Techniques: Simulation of circular movement with modulo arithmetic.
Time Complexity: O(n) where n is the number of stations (worst case is when they meet at the last possible step).
Space Complexity: O(1) - only using a constant amount of extra space.
*/

// https://github.com/VaHiX/codeForces/