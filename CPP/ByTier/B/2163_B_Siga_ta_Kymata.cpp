// Problem: CF 2163 B - Siga ta Kymata
// https://codeforces.com/contest/2163/problem/B

/*
Purpose: This code solves the problem of setting specific bits in a binary string 's' based on a permutation 'p' and a target binary string 'x'. 
         It uses at most 5 operations to ensure that for all positions where x[i] is '1', s[i] is also '1'. 
         The approach involves identifying the positions of minimum and maximum elements in the permutation and using specific intervals to set required bits.

Algorithms/Techniques:
- Greedy interval-based bit setting
- Preprocessing to find min and max positions

Time Complexity: O(n) per test case, where n is the size of the permutation
Space Complexity: O(n) for storing the permutation and the binary string x

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    string x;
    cin >> x;
    int f, l;
    // If first or last position in x is 1, it is impossible to satisfy the condition
    if (x[0] == '1' || x[n - 1] == '1') {
      cout << -1 << "\n";
      continue;
    }
    int mx, mn;
    // Find positions of maximum and minimum elements in the permutation
    for (int i = 0; i < n; ++i) {
      if (v[i] == n)
        mx = i;
      if (v[i] == 1)
        mn = i;
    }
    // If either the position of max or min element in permutation has 1 in x, it's impossible
    if (x[mx] == '1' || x[mn] == '1') {
      cout << -1 << "\n";
      continue;
    }
    // Output 5 operations to set required bits in s
    cout << 5 << "\n";
    cout << 1 << " " << mx + 1 << "\n";  // Operation to set bits between 1 and max element
    cout << 1 << " " << mn + 1 << "\n";  // Operation to set bits between 1 and min element
    cout << min(mn + 1, mx + 1) << " " << max(mn + 1, mx + 1) << "\n"; // Operation to set bits between min and max elements
    cout << mn + 1 << " " << n << "\n";  // Operation to set bits from min to end
    cout << mx + 1 << " " << n << "\n";  // Operation to set bits from max to end
  }
}


// https://github.com/VaHiX/CodeForces/