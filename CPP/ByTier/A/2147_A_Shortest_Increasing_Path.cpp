// Problem: CF 2147 A - Shortest Increasing Path
// https://codeforces.com/contest/2147/problem/A

/*
 * Code Purpose: Solves the problem of finding the minimum number of steps to reach a point (x, y)
 *               in a grid under specific movement constraints:
 *               - Steps alternate between x and y axes (odd steps on x, even on y)
 *               - Each step must be strictly longer than the previous one
 *               - First step must be along x-axis
 *
 * Algorithms/Techniques: Greedy approach with case analysis based on the values of x and y.
 *
 * Time Complexity: O(1) per test case - constant time operations.
 * Space Complexity: O(1) - only using a fixed amount of variables.
 */

#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) { // Process each test case
    int a, b;
    cin >> a >> b; // Read x and y coordinates
    
    if (a < b)
      cout << 2; // If x < y, we can reach (x,y) in 2 steps:
                 // Step 1: Move x units along x-axis (from 0,0 to x,0)
                 // Step 2: Move y-x units along y-axis (from x,0 to x,y)
                 // Since step 1 is x and step 2 is y-x, we need y-x > x => y > 2*x
                 // But when x < y, the smallest valid second step is y, which always satisfies 
                 // the increasing constraint as long as a <= b.
    else if (a - 1 > b && b != 1)
      cout << 3; // If we're in a case where we need 3 steps due to the strict increasing rule,
                 // this checks if a-1 is greater than b and b isn't 1 to allow for three steps:
                 // Step 1: move 1 unit on x-axis (0,0) -> (1,0)
                 // Step 2: move a units on y-axis (1,0) -> (1,a)
                 // Step 3: move b units on x-axis (1,a) -> (b+1,a), so we have reached (b,a).
                 // This is valid if a > b and a - 1 > b, but also requires that b != 1 to not be invalid.
    else
      cout << -1; // For all other cases, reaching the target point with valid strict increasing step lengths is impossible.
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/