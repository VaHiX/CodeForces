// Problem: CF 1744 F - MEX vs MED
// https://codeforces.com/contest/1744/problem/F

/*
Code Purpose:
This code solves the problem of counting subsegments where the MEX (minimum excludant) of the subsegment is greater than its MED (median).
It uses a clever observation based on the positions of elements in the permutation to efficiently compute the result.

Algorithms/Techniques:
- Observation-based algorithm
- Preprocessing positions of elements in permutation
- Two-pointer technique with optimization
- Mathematical calculation of valid subsegments

Time Complexity: O(n) amortized per test case, since each element is processed a constant number of times.
Space Complexity: O(n) for storing the permutation positions.

*/
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e5 + 10;
long long T, p[N], n, l, r, re, me, i, x, L;
int main() {
  for (cin >> T; T--;) {
    cin >> n;
    for (i = 1; i <= n; i++)
      cin >> x, p[x] = i; // Store the position of each value (0 to n-1) in the permutation
    l = r = p[0], re = 1, me = 0; // Initialize leftmost, rightmost positions and result
    for (L = 2; L <= n; L++) {
      me = (L - 1) / 2; // Calculate the median index for a subsegment of length L
      l = min({l, p[me], n + 1 - L}); // Update the left boundary
      r = max({r, p[me], L}); // Update the right boundary
      re += max(0ll, L - r + l); // Add valid subsegments count to the result
    }
    cout << re << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/