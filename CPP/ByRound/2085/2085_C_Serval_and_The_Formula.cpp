// Problem: CF 2085 C - Serval and The Formula
// https://codeforces.com/contest/2085/problem/C

/*
C. Serval and The Formula
Algorithms/Techniques: Bit manipulation, properties of XOR and addition
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem asks to find a non-negative integer k such that (x+k)+(y+k) = (x+k)⊕(y+k).
This is only possible if there's no carry in the binary addition of (x+k) and (y+k), 
which happens when x+k and y+k are disjoint in their binary representation (i.e., they don't share any 1-bit positions). 

We observe that:
- If x == y, then (x+k)⊕(y+k) = 0, but (x+k)+(y+k) = 2*(x+k), so the equation cannot hold.
- Otherwise, we can use the fact that k = (1 << 32) - max(x, y) works under certain conditions.

This approach uses bit manipulation to construct a valid k when x != y.
*/

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    long long x, y;
    cin >> x >> y;
    if (x == y)
      cout << "-1\n";           // When x equals y, no solution exists because XOR would be 0 and sum would be 2*x > 0
    else
      cout << (1ll << 32) - max(x, y) << "\n";  // Construct k to make the equation valid using bit manipulation
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/