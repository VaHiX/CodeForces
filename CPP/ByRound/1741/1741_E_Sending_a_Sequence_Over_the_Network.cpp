// Problem: CF 1741 E - Sending a Sequence Over the Network
// https://codeforces.com/contest/1741/problem/E

/*
Algorithm: Dynamic Programming with Map
Approach:
- This problem is about determining whether a given sequence b can be a valid representation of a sequence a sent over a network.
- The key insight is to simulate the process of segmenting a and reconstructing b.
- We use a boolean map 'f' where f[i] represents whether it's possible to reach position i in the reconstruction.
- Initially, f[0] = true (base case).
- For each element x in b:
  - We can either place x at the end of a segment (f[i + x] |= f[i - 1])
  - Or we can place x as the start (f[i] |= f[i - x - 1])
- If f[n] is true, then it's possible to construct such sequence a.

Time Complexity: O(n log n) - due to map operations (log n for insertion/access)
Space Complexity: O(n) - for the map storage

*/
#include <iostream>
#include <map>

using namespace std;
int t, n, x;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    map<int, bool> f;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
      cin >> x;
      // Check if we can extend a segment ending at i-1 with length x
      f[i + x] |= f[i - 1];
      // Check if we can start a new segment at position i with length x
      f[i] |= f[i - x - 1];
    }
    cout << (f[n] ? "YES\n" : "NO\n");
  }
}


// https://github.com/VaHiX/CodeForces/