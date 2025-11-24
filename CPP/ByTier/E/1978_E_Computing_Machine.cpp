// Problem: CF 1978 E - Computing Machine
// https://codeforces.com/contest/1978/problem/E

/*
Purpose: Solve the problem of maximizing the number of 1s in a substring of string s
         by applying specific operations on substrings of s and t.

Algorithms/Techniques:
- Preprocessing: Two passes to simulate the operations and build updated strings n_s and n_t.
- Query processing: Use prefix sums and correction terms to efficiently compute the count of 1s in any interval.

Time Complexity: O(n + q) per test case, where n is the length of the strings and q is the number of queries.
Space Complexity: O(n) for storing the strings and prefix sums.

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    string n_s = s, n_t = t;
    auto val = [](char &c) { return c == '1'; }; // Lambda to check if character is '1'
    
    // First pass: update n_t based on s
    for (int i = 0; i < n - 2; i++)
      if (!(val(s[i]) | val(s[i + 2]))) // If s[i] and s[i+2] are both 0
        n_t[i + 1] = '1'; // Set n_t[i+1] to 1
    
    // Second pass: update n_s based on n_t
    for (int i = 0; i < n - 2; i++)
      if (val(n_t[i]) & val(n_t[i + 2])) // If n_t[i] and n_t[i+2] are both 1
        n_s[i + 1] = '1'; // Set n_s[i+1] to 1
    
    // Lambda to check if original and updated characters differ
    auto s_diff = [&](int i) { return s[i] != n_s[i]; };
    auto t_diff = [&](int i) { return t[i] != n_t[i]; };
    
    // Compute prefix sum for n_s to quickly get count of 1s in a range
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++)
      pref[i] = pref[i - 1] + val(n_s[i - 1]);
    
    int q;
    cin >> q;
    while (q--) {
      int l, r;
      cin >> l >> r;
      int len = r - l + 1, ans = 0;
      
      // Handle different lengths of intervals
      if (len == 1) {
        ans = val(s[l - 1]); // Only the first character
      } else if (len == 2) {
        ans = val(s[l - 1]) + val(s[l]); // Both characters
      } else if (len == 3) {
        // Three characters, plus one possible 1 from operation
        ans = val(s[l - 1]) + val(s[l]) + val(s[l + 1]);
        ans += (!val(s[l]) & val(t[l - 1]) & val(t[l + 1])); // Add 1 if conditions met
      } else {
        // General case: use prefix sum and adjust for differences
        ans = pref[r] - pref[l - 1]; // Base count from prefix sum
        ans -= s_diff(r - 1) + s_diff(l - 1); // Subtract changes at boundaries
        ans -= (s_diff(r - 2) & t_diff(r - 1)); // Adjust for right boundary changes
        ans -= (s_diff(l) & t_diff(l - 1)); // Adjust for left boundary changes
      }
      cout << ans << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/