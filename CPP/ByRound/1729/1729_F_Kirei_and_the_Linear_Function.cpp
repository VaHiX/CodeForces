// Problem: CF 1729 F - Kirei and the Linear Function
// https://codeforces.com/contest/1729/problem/F

/*
Purpose: Solve the problem of finding two substrings of length w such that a specific modular arithmetic condition holds.
Approach:
- Precompute prefix sums for digit strings to quickly calculate substring values modulo 9.
- Group all substrings of length w by their value modulo 9.
- For each query, determine valid pairs of substrings based on the formula (v(L1) * v(l,r) + v(L2)) % 9 == k.

Time Complexity: O(n * w + m * 9^2) 
Space Complexity: O(n + 9 * w) 
*/
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define ll long long
int main() {
  int Tit = 1;
  cin >> Tit;
  while (Tit--) {
    string s;
    cin >> s;
    int n = s.length();
    int w, m;
    cin >> w >> m;
    // Precompute prefix sums for efficient substring sum calculation
    vector<int> f(n + 1);
    for (int i = 0; i < n; i++)
      f[i + 1] = f[i] + s[i] - '0';
    
    // Group substrings of length w by their sum mod 9
    vector<int> a[9];
    for (int i = 0; i + w <= n; i++)
      a[(f[i + w] - f[i]) % 9].push_back(i);
    
    while (m--) {
      // Initialize answer with large values
      array<int, 2> ans{n, n};
      int l, r, k;
      cin >> l >> r >> k;
      // Get the value of query substring modulo 9
      int x = (f[r] - f[l - 1]) % 9;
      
      // Check all possible pairs of groups for valid combinations
      for (int u = 0; u < 9; u++) {
        // Case 1: Two substrings from the same group
        if (a[u].size() > 1 && (u * x + u) % 9 == k)
          ans = min(ans, {a[u][0], a[u][1]});
        
        // Case 2: Two substrings from different groups
        for (int v = 0; v < 9; v++) {
          if (u != v && a[u].size() && a[v].size() && (u * x + v) % 9 == k)
            ans = min(ans, {a[u][0], a[v][0]});
        }
      }
      
      // Output result or -1 -1 if not found
      if (ans[0] == n)
        cout << "-1 -1\n";
      else
        cout << ans[0] + 1 << ' ' << ans[1] + 1 << endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/