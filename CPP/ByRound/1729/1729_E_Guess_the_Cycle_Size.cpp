// Problem: CF 1729 E - Guess the Cycle Size
// https://codeforces.com/contest/1729/problem/E

/*
 * Problem: Guess the Cycle Size
 * 
 * Purpose: This interactive problem requires determining the number of vertices
 *          in a hidden cyclic graph by querying distances between pairs of vertices.
 *          The graph is a cycle with n vertices (3 <= n <= 10^18).
 * 
 * Algorithm:
 * 1. First, we find an upper bound on n by querying distances from vertex 1 to increasing
 *    vertex numbers until we get -1 (indicating the vertex doesn't exist).
 * 2. Then, for a candidate vertex k (starting from 2), we query both directions:
 *    - ? 1 k: distance from 1 to k
 *    - ? k 1: distance from k to 1 (this will be different due to the cycle structure)
 *    3. If the two distances are different, we calculate n as x + y.
 *    4. Otherwise, we continue to increase k.
 * 
 * Time Complexity: O(log n) for the first loop (since we're doubling the search space),
 *                  and O(1) for each query. Overall: O(log n) queries.
 * Space Complexity: O(1) - only using constant extra space.
 */

#include <iostream>

using namespace std;
int main() {
  long long x, y;
  // Loop from vertex 2 to 26 to find the approximate size of the cycle
  for (int i = 2; i < 27; i++) {
    // Query distance from vertex 1 to vertex i
    cout << "? 1 " << i << endl;
    cin >> x;
    // If we get -1, vertex i doesn't exist => size of cycle is i-1
    if (x == -1) {
      cout << "! " << i - 1 << endl;
      break;
    }
    // Query distance from vertex i to vertex 1
    cout << "? " << i << " 1" << endl;
    cin >> y;
    // If the distances differ, we've found a pair of vertices that can help us compute n
    if (x != y) {
      cout << "! " << x + y << endl;
      break;
    }
  }
}


// https://github.com/VaHiX/CodeForces/