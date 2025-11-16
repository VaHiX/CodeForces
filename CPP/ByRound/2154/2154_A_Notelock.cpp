// Problem: CF 2154 A - Notelock
// https://codeforces.com/contest/2154/problem/A

/*
Purpose: This code solves the "Notelock" problem where we need to find the minimum number of positions to protect in a binary string to ensure Teto cannot change any '1' to '0'. The algorithm greedily checks each '1' and determines if it can be changed, based on whether any '1' exists in the previous k-1 positions (excluding the current one). If no such '1' exists, we must protect this position to prevent modification.

Algorithms/Techniques:
- Greedy Algorithm: For each '1' in the string, we check whether it's safe to change it (i.e., no '1' in the previous k-1 positions).
- Linear Scan: We iterate through the string once to process all '1's.

Time Complexity: O(n * k), where n is the length of string s and k is the given parameter. In the worst case, for each '1', we scan up to k-1 previous characters.
Space Complexity: O(1), as we use only a constant amount of extra space (variables like cnt, ind, z, fl) regardless of input size.

*/
#include <iostream>
#include <string>

using namespace std;
#define int long long
const int MOD = 1e9 + 7;
void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  int cnt = 0; // Counter for protected positions
  for (int i = 0; i < n; ++i) {
    if (s[i] == '1') { // If current character is '1'
      int ind = i - 1; // Start checking from the previous index
      int z = k - 1;   // Number of positions to check backward
      bool fl = false; // Flag to indicate if a '1' is found in the window
      while (z > 0 && ind >= 0) { // Loop through k-1 previous characters
        if (s[ind] == '1') { // If a '1' is found in the window
          fl = true;       // Mark that we can't protect this position
          break;
        }
        --z;     // Decrement remaining checks
        --ind;   // Move to the previous index
      }
      if (!fl) // If no '1' was found in the previous k-1 positions
        ++cnt; // We must protect this '1'
    }
  }
  cout << cnt << endl;
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/