// Problem: CF 2078 E - Finding OR Sum
// https://codeforces.com/contest/2078/problem/E

/*
E. Finding OR Sum
Interactive problem to determine two hidden integers x and y using at most 2 queries.
The goal is to compute (m | x) + (m | y) given that x, y, m are in range [0, 2^30).

Algorithms/Techniques:
- Bit manipulation and systematic query design
- Uses two specific queries to gather information about bits of x and y
- Calculates x and y from the responses using bitwise logic

Time Complexity: O(1) per test case (constant number of operations)
Space Complexity: O(1) (constant extra space used)

*/

#include <iostream>

#define int long long
using namespace std;
const int o = 1e6 + 3;
const int mod = 998244353;
int n, m, T, k, b[o], ans, a[o], d[o];
char c[o], l[o], r[o];

signed main() {
  ios::sync_with_stdio(0);
  cin >> T;
  int u = 0x2aaaaaaa, v = 0x15555555; // Predefined constants for queries
  while (T--) {
    int x = 0, y = 0, l, r;
    cout << u << "\n";      // First query with constant u
    cout.flush();           // Ensure output is sent
    cin >> l;               // Read result of first query
    cout << v << "\n";      // Second query with constant v
    cout.flush();           // Ensure output is sent
    cin >> r;               // Read result of second query
    
    // Adjust l and r to extract bit information about x and y
    l -= (u << 1), r -= (v << 1);
    
    // Process each bit position from 0 to 29
    for (int i = 0; i < 30; i++) {
      int q;
      // Alternate between using l and r depending on bit position parity
      if (i & 1)
        q = r;
      else
        q = l;
      
      // Determine bits of x and y based on the query results
      if (q & (1 << i))
        x |= (1 << i);       // Set bit in x
      else if (q & (1 << (i + 1)))
        x |= (1 << i), y |= (1 << i); // Set bits in both x and y
    }
    
    cout << "!" << "\n";    // Signal end of queries
    cout.flush();           // Ensure output is sent
    
    cin >> m;               // Read value of m from judge
    cout << (m | x) + (m | y) << "\n";  // Output final answer
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/