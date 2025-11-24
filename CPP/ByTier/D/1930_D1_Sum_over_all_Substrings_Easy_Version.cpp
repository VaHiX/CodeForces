// Problem: CF 1930 D1 - Sum over all Substrings (Easy Version)
// https://codeforces.com/contest/1930/problem/D1

/*
 * Code Purpose: 
 *   This code solves the problem of computing the sum of f(p) over all substrings of a given binary string s.
 *   For each substring p, f(p) is defined as the minimum number of 1s in any p-good binary string of the same length.
 *   A binary string q is p-good if for every position i in p, the character p[i] is a mode of the substring q[l..r] 
 *   where l <= i <= r.
 *   
 *   The algorithm uses a brute-force approach to iterate over all substrings and computes the required value 
 *   by checking for valid 1s which must appear in at least half the length of the substring (rounded up).
 *   
 * Algorithms/Techniques:
 *   - Brute Force over all substrings
 *   - Mode checking logic using counting and ceiling division
 *   
 * Time Complexity: O(n^3)
 *   Where n is the length of the input string s. 
 *   For each of the O(n^2) substrings, we potentially check O(n) positions.
 *   
 * Space Complexity: O(1) 
 *   Only using a constant amount of extra space.
 */

#include <stdint.h>
#include <iostream>
#include <string>

#define int long long
#define all(a) begin(a), end(a)
#define sz(a) (a).size()
#define forn(i, n) for (int i = 0; i < (n); i++)
typedef long long LL;
typedef long double LD;
using namespace std;

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  int ans = 0;
  for (int l = 0; l < n; l++) {
    for (int r = l; r < n; r++) {
      int R = -1;
      for (int i = l; i <= r; i++) {
        // If s[i] is '1' and it hasn't been covered yet by a previous '1' in our greedy selection
        if (s[i] == '1' && i > R) {
          ans++; // Increment count for this required 1
          R = i + 2; // Mark the next valid position after greedily selecting this 1
        }
      }
    }
  }
  cout << ans << '\n';
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(false);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/