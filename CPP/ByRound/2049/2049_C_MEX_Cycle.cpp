// Problem: CF 2049 C - MEX Cycle
// https://codeforces.com/contest/2049/problem/C

/*
Problem: MEX Cycle
Purpose: Assign non-negative integers to dragons in a circle such that each dragon's value equals the MEX of its friends' values.
Algorithm: Based on the structure of the graph (cycle with additional edge between x and y), we determine the assignment using parity and pattern recognition.
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (excluding output array)

Approach:
- The graph is a cycle with an additional edge between nodes x and y.
- We analyze two cases:
  1. When n is even:
     a. If (y - x) is even, we assign alternating values (0,1,0,1,...), but specially handle x to be 2.
     b. If (y - x) is odd, we assign alternating values (0,1,0,1,...).
  2. When n is odd:
     a. If (y - x) is even, special handling for x with 0->1->2 pattern, then alternating.
     b. If (y - x) is odd, we use a base alternating pattern and add 0,1,2 at the end.

*/
#include <iostream>

using namespace std;
#define itn int
#define tin int
#define nit int
#define longlong long long
typedef long long ll;
typedef unsigned long long ull;
int n, x, y;
int a[114514];
void solve() {
  cin >> n >> x >> y;
  if (n % 2 == 0) {
    if ((y - x) % 2 == 0) {
      int res = 0;
      for (int i = 1; i <= n; i++) {
        if (i != x) {
          cout << res << ' '; // Assign current value to all nodes except x
        }
        if (i == x)
          cout << 2 << ' '; // Node x gets value 2 (special handling)
        res ^= 1; // Toggle between 0 and 1 using XOR
      }
    } else {
      int res = 1;
      for (int i = 1; i <= n; i++) {
        cout << res << ' '; // Alternating 1,0,1,0...
        res = (res + 1) % 2; // Toggle between 0 and 1
      }
    }
  } else {
    if ((y - x) % 2 == 0) {
      int res = 0;
      for (int i = 1; i <= n; i++) {
        if (i != x)
          cout << res << ' '; // Assign current value to all nodes except x
        if (i == x) {
          cout << res << ' '; // Assign same value as current res to x
          if (res == 0) {
            cout << 1 << ' ' << 2 << ' '; // Special pattern for x=0
            i += 2; // Skip next two indices
          } else {
            cout << 2 << ' '; // Special pattern for x=1
            i++; // Skip next index
          }
          res = 1; // Reset res to 1 for following nodes
        }
        res = (res + 1) % 2; // Toggle between 0 and 1
      }
    } else {
      int res = 0;
      for (int i = 1; i <= n - 3; i++) {
        cout << res << ' '; // Basic alternating pattern
        res = (res + 1) % 2; // Toggle between 0 and 1
      }
      cout << 0 << ' ' << 1 << ' ' << 2; // Final three nodes get 0,1,2
    }
  }
  cout << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/