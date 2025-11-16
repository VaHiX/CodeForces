// Problem: CF 1984 C2 - Magnitude (Hard Version)
// https://codeforces.com/contest/1984/problem/C2

/* 
C2. Magnitude (Hard Version)
Algorithms/Techniques: Dynamic Programming with State Tracking
Time Complexity: O(n) per test case
Space Complexity: O(1)

This problem involves finding the number of ways to choose between two operations
at each step such that the final value of a cumulative sum reaches its maximum possible value.
We use dynamic programming where each state tracks:
- The current maximum absolute value achieved (a[0])
- Number of ways to achieve that value (a[1])
- The actual cumulative sum (a[2])
- Number of ways to reach that sum (a[3])

At every step, we compute new states based on whether we take option 1 (add) or option 2 (absolute add).
We track combinations using modular arithmetic.
*/

#include <algorithm>
#include <bits/std_abs.h>
#include <iostream>
#include <string.h>
using namespace std;
const int mod = 998244353;
int T, n;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    long long a[4] = {0, 1, 0, 1}, b[4]; // a[0]=max_abs_value, a[1]=count_ways_max, a[2]=current_sum, a[3]=count_ways_sum
    for (int i = 0; i < n; i++) {
      int w;
      cin >> w;
      // Compute new maximum absolute value based on both options (add or absolute add)
      b[0] = max(abs(a[0] + w), abs(a[2] + w)); // b[0] := new_max_abs_value
      b[1] = 0; // reset count for new max
      if (b[0] == abs(a[0] + w)) // if adding gave max value
        b[1] = (b[1] + a[1]) % mod;
      if (b[0] == a[0] + w) // if not negating was better, same as adding directly
        b[1] = (b[1] + a[1]) % mod;
      if (a[0] != a[2] && b[0] == abs(a[2] + w)) // case where previous sum led to larger absolute value when negated
        b[1] = (b[1] + a[3]) % mod;
      b[2] = a[2] + w; // update cumulative sum
      b[3] = a[3]; // update ways to reach this sum
      if (b[2] >= 0)
        b[3] = b[3] * 2 % mod; // double the number of ways since we can now go both + or - path
      memcpy(a, b, sizeof(b)); // transfer new values for next iteration
    }
    cout << b[1] << '\n';
  }
}


// https://github.com/VaHiX/codeForces/