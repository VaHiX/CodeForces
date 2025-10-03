// Problem: CF 2093 F - Hackers and Neural Networks
// https://codeforces.com/contest/2093/problem/F

/*
F. Hackers and Neural Networks
Algorithms/Techniques: Greedy, Simulation, String Matching

Time Complexity: O(m * n * t) where t is the number of test cases, m is the number of neural networks, n is the length of arrays.
Space Complexity: O(n * m) for storing the input strings and auxiliary arrays.

Problem Description:
Given an array 'a' of length n, and m neural networks each producing a different version of the same array,
we want to find the minimum number of operations to construct array 'a' starting from an array of blanks (*).
Each operation involves selecting a neural network and replacing one blank with a value from that network's array.
If some element in 'a' cannot be obtained through any neural network, output -1.

Approach:
For each test case:
1. Read input arrays: target array 'a' and m neural network arrays.
2. For each neural network, compute how many positions match the target array 'a'.
3. Keep track of the maximum such matches (mx).
4. Also record which elements of 'a' are covered by at least one neural network (using array 'p').
5. If any element of 'a' is not covered by any neural network, return -1.
6. Otherwise, calculate the minimal operations:
   - For positions matched in some network: 1 operation each
   - For unmatched positions: 3 operations (replace blank with value from one net + replace with another + final correction)
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define int long long
string a[508]; // Target array of strings
int n, m;      // Length of array and number of neural networks
bool p[508];   // Track if each index in 'a' is covered by at least one network

void solve() {
  int mx = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[i] = false; // Initialize target array and tracking array
  
  for (int i = 1; i <= m; i++) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
      string tmp;
      cin >> tmp;
      if (tmp == a[j]) { // If current network's string matches target
        sum++;          // Count how many matches
        p[j] = true;    // Mark that index is covered by at least one network
      }
    }
    mx = max(mx, sum); // Keep track of maximum number of matches for any single network
  }
  
  for (int i = 1; i <= n; i++) {
    if (p[i] == false) // If any index is not covered by any network
      return void(cout << -1 << '\n'); // Not possible to construct target array
  }
  
  int ans = mx + (n - mx) * 3; // Minimum operations needed:
                               // 1. We use one operation per position matched in best network: mx
                               // 2. For remaining positions, 3 operations needed for replacement: (n - mx) * 3
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/