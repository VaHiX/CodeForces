// Problem: CF 2104 E - Unpleasant Strings
// https://codeforces.com/contest/2104/problem/E

/*
E. Unpleasant Strings
Algorithm: Suffix automaton / Dynamic Programming with precomputation
Time Complexity: O(n * k + sum of lengths of all queries)
Space Complexity: O(n * k + sum of lengths of all queries)

This problem involves finding the minimum number of characters to append to a query string 
so that it stops being a subsequence of the given string s. 

We use preprocessing with dynamic programming:
- f[i][j] stores the next occurrence of character j starting from position i in s
- dis[i] stores the minimum number of characters needed to make a string starting at position i unpleasant
- la[j] keeps track of the last occurrence of each character

For each query, we simulate the process of matching against f to find where we would need to append characters.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int n, k, q, f[1000005][26], la[26], ti[1000005], dis[1000005];
string s, st[200005];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k >> s >> q;
  s = " " + s; // Add padding to make indexing easier
  for (int i = 0; i < k; i++) {
    f[n + 1][i] = la[i] = n + 1; // Initialize farthest positions as beyond string
  }
  dis[n + 1] = 0; // Base case: no need to append anything at end of string
  for (int i = n; i; i--) {
    dis[i] = 1e9; // Initialize with large value
    for (int j = 0; j < k; j++) {
      f[i][j] = la[j]; // Store next occurrence of character j
      dis[i] = min(dis[i], dis[la[j]] + 1); // Update minimum distance to make it unpleasant
    }
    la[s[i] - 'a'] = i; // Update last seen index of current character
  }
  for (int i = 0; i < k; i++) {
    f[0][i] = la[i]; // Initialize state at beginning of string
  }
  for (int i = 1; i <= q; i++) {
    cin >> st[i];
    int fa = 0;
    for (int j = 0; j < st[i].size(); j++) {
      fa = f[fa][st[i][j] - 'a']; // Move through transitions
    }
    cout << dis[fa] << "\n"; // Print result from precomputed values
  }
}


// https://github.com/VaHiX/codeForces/