// Problem: CF 1759 F - All Possible Digits
// https://codeforces.com/contest/1759/problem/F

/*
Code Purpose:
This program determines the minimum number of operations required to ensure that all digits from 0 to p-1 appear at least once in the number x written in base p.
Each operation increments the number x by 1, which might cause carryovers affecting the digits.

Algorithms/Techniques:
- Digit-by-digit simulation with carry handling.
- Tracking used digits using a map.
- Efficient computation of how many new digits are needed by simulating carries.
- Optimization to avoid unnecessary iterations.

Time Complexity: O(n * p) in worst case due to nested loops, but typically much better in practice.
Space Complexity: O(p) for the map storing digit usage.

*/
#include <iostream>
#include <map>

using namespace std;
int t, n, p, i, c, ans, a[110];
map<int, int> m;
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> p;
    for (int i = 1; i <= n; i++)
      cin >> a[i], m[a[i]] = 1; // Read digits and mark them as present
    ans = p; // Initially assume we need p operations to cover all digits
    i = a[n]; // Start checking from the least significant digit
    // Count how many digits in the range [0, i] are missing
    for (; m[i] && i > 0; i--)
      ans--;
    if (i > 0) { // If there is a gap in used digits
      c = n - 1; // Start from second to last digit
      // Find the first digit that doesn't produce a carry when incremented
      while (c && a[c] == p - 1)
        c--;
      // If carry propagation leads back to the gap
      if ((a[c] + 1) % p == i) 
        for (i--, ans--; m[i] && i > 0; i--)
          ans--;
    } else
      // If we've covered from 0 up to i (which is 0), check backward
      for (; m[i] && ans != 0; i = (i + p - 1) % p)
        ans--;
    cout << ans << '\n';
    m.clear(); // Clear the map for next test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/