// Problem: CF 1722 E - Counting Rectangles
// https://codeforces.com/contest/1722/problem/E

/*
Code Purpose:
This code solves the problem of counting rectangles that fit within given bounds for multiple queries.
It uses a 2D prefix sum array to efficiently compute the total area of rectangles satisfying the constraints.
The algorithm pre-processes rectangle data into a 2D prefix sum array, then answers each query in O(1) time.

Algorithms/Techniques:
- 2D Binary Indexed Tree / 2D Prefix Sum
- Coordinate compression (implicit through fixed size array)

Time Complexity: O(N + Q) per test case where N is number of rectangles and Q is number of queries.
Space Complexity: O(1000 * 1000) = O(10^6) which is acceptable as per constraints.

*/
#include <iostream>

using namespace std;
int main() {
  long long t, n, q, x, y, z, w;
  cin >> t;
  while (t--) {
    cin >> n >> q;
    long long A[1001][1001]{}; // 2D prefix sum array initialized to 0
    while (n--) {
      cin >> x >> y;
      A[x][y] += x * y; // Add area of rectangle at position (x, y)
    }
    // Build 2D prefix sum
    for (int i{1}; i <= 1000; i++)
      for (int j{1}; j <= 1000; j++)
        A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
    while (q--) {
      cin >> x >> y >> z >> w;
      // Query for rectangles with height in (x, z) and width in (y, w)
      // Using inclusion-exclusion principle on 2D prefix sums
      cout << A[z - 1][w - 1] - A[x][w - 1] - A[z - 1][y] + A[x][y] << '\n';
    }
  }
}


// https://github.com/VaHiX/CodeForces/