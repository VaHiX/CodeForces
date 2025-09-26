// Problem: CF 2136 D - For the Champion
// https://codeforces.com/contest/2136/problem/D

/*
Problem: D. For the Champion
Algorithms/Techniques: Interactive problem with Manhattan distance queries; Binary search approach using directional moves to determine initial coordinates.
Time Complexity: O(n) per test case due to pre-processing and constant number of moves (10).
Space Complexity: O(n) for storing anchor points.
*/

#include <algorithm>
#include <iostream>

#define N 200009
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3fll
using namespace std;
int n;
ll a, b; // a stores max(x+y), b stores max(x-y) from anchor points
ll u, v; // u and v will store the computed components after queries

void solve() {
  cin >> n;
  a = b = -INF; // Initialize to negative infinity to find maximums
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    a = max(a, (ll)x + y); // Compute maximum of x+y across all anchor points
    b = max(b, (ll)x - y); // Compute maximum of x-y across all anchor points
  }
  
  // Move up by 10^9 and query Manhattan distance
  cout << "? U 1000000000" << endl;
  cin >> u;
  // Query again to get consistent result (possibly a bug in code - repeated queries)
  cout << "? U 1000000000" << endl;
  cin >> u;
  
  // Move right by 10^9 and query Manhattan distance
  cout << "? R 1000000000" << endl;
  cin >> u;
  // Query again (repeated)
  cout << "? R 1000000000" << endl;
  cin >> u;
  
  // Move down by 10^9 and query Manhattan distance
  cout << "? D 1000000000" << endl;
  cin >> v;
  // Query again (repeated)
  cout << "? D 1000000000" << endl;
  cin >> v;
  // Query again (repeated)
  cout << "? D 1000000000" << endl;
  cin >> v;
  // Query again (repeated)
  cout << "? D 1000000000" << endl;
  cin >> v;
  
  // Adjust u and v using the max values computed earlier
  u += a;       // Add max(x+y)
  v += b;       // Add max(x-y)
  
  // Shift by large constant (4*10^9) to adjust for coordinate system
  u -= 4000000000ll;
  v -= 4000000000ll;

  // Output calculated initial coordinates using the derived formulas:
  // X = (u + v) / 2; Y = (u - v) / 2
  cout << "!" << " " << (u + v) / 2 << " " << (u - v) / 2 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/