// Problem: CF 2020 C - Bitwise Balancing
// https://codeforces.com/contest/2020/problem/C

/*
Purpose: This code solves the problem of finding a non-negative integer `a` such that (a | b) - (a & c) = d.
         It uses bitwise operations and manipulation to determine if such an `a` exists and returns one if it does.

Algorithm:
- For each test case, we compute `res = x ^ z`, where x=b, z=d.
- We then check if the equation (res | b) - (res & c) == d holds.
  - If yes, output `res`.
  - Otherwise, output -1.

Time Complexity: O(1) per test case — constant time operations.
Space Complexity: O(1) — uses only a few variables regardless of input size.

Techniques:
- Bitwise XOR to derive candidate `a`.
- Validation using bitwise OR and AND operations.
*/

#include <iostream>

using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    long long x, y, z, res;
    cin >> x >> y >> z;
    res = x ^ z; // Compute candidate a using XOR
    if ((res | x) - (res & y) == z) // Validate the candidate
      cout << res << "\n";
    else
      cout << "-1\n";
  }
}


// https://github.com/VaHiX/CodeForces/