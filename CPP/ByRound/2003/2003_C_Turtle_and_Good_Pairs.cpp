// Problem: CF 2003 C - Turtle and Good Pairs
// https://codeforces.com/contest/2003/problem/C

/*
Purpose:
This code solves the problem of reordering a string to maximize the number of "good pairs".
A good pair (i, j) is defined as either:
1. s[i] == s[j], or
2. There exists a k such that i <= k < j, and:
   - s[k] != s[k + 1]
   - s[k] != s[i] or s[k + 1] != s[j]

The strategy is to greedily place characters to maximize good pairs:
- Prioritize placing characters that are different from the last placed character.
- When no such character is available, fill with the remaining characters of the last used type.

Algorithms/Techniques:
- Greedy character placement based on frequency and avoiding adjacent duplicates.
- Frequency counting of characters.

Time Complexity: O(n) per test case (since there are at most 26 characters and we do bounded iterations).
Space Complexity: O(1) (fixed size frequency array of 26 elements).
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <stddef.h>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace __gnu_pbds;
#define ll long long
#define vi vector<int>
#define ii pair<ll, ll>
#define fi first
#define se second
#define pb push_back
#define vll vector<ll>
typedef tree<ll, null_type, less<ll>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
const int N = 5e3 + 9, K = 500, OFF = 102;
void solve(int tc) {
  int n;
  string s;
  cin >> n >> s;
  vi f(26, 0); // Frequency array for 26 lowercase letters
  for (int i = 0; i < n; i++)
    f[s[i] - 'a']++; // Count frequency of each character
  int lst = -1; // Tracks last placed character index
  for (int i = 0; i < n; i++) {
    int ys = 0; // Flag to check if any character was placed
    for (int j = 0; j < 26; j++) {
      // Skip if character is same as last or frequency is zero
      if (j == lst || !f[j])
        continue;
      char cur = 'a' + j; // Get current character
      cout << cur; // Place the character
      f[j]--; // Decrease frequency
      lst = j; // Update last character
      ys = 1; // Mark that a character was placed
    }
    if (!ys) { // If no valid character found, place remaining of last character
      for (int j = 0; j < f[lst]; j++) {
        char cur = 'a' + lst;
        cout << cur;
      }
      break; // Exit loop
    }
  }
  cout << "\n";
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tc = 1;
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    solve(t);
  }
}


// https://github.com/VaHiX/CodeForces/