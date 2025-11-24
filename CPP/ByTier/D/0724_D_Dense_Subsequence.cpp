// Problem: CF 724 D - Dense Subsequence
// https://codeforces.com/contest/724/problem/D

/*
Purpose: To find the lexicographically smallest string that can be formed by
selecting a subsequence of the input string such that every contiguous
subsegment of length m has at least one selected symbol.

Algorithm:
1. We use a greedy approach to select the smallest character in each window of
size m.
2. For each window, we find the minimum character and mark its position as used.
3. After processing all windows, we append any unused characters that are
smaller than the maximum selected character.
4. Finally, we sort the selected characters to obtain the lexicographically
smallest string.

Time Complexity: O(n * m) where n is the length of the string s.
Space Complexity: O(n) for storing the result and used flags.

*/

#include <algorithm>
#include <iostream>
#include <stddef.h>
#include <string>
#include <vector>

#define int long long
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pii pair<int, int>
using namespace std;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int m;
  cin >> m;
  string s;
  cin >> s;
  vector<char> a;             // Stores the selected characters
  vector<int> used(s.size()); // Tracks which positions are already selected
  int p = 0;                  // Current position in the string
  char mx = 'a';              // Maximum character selected so far
  while (p + m <= s.size()) {
    int mn = p; // Index of the minimum character in current window
    for (int i = p; i < p + m; i++) {
      if (s[mn] >= s[i])
        mn = i;
    }
    a.pb(s[mn]);         // Add the minimum character to result
    mx = max(mx, s[mn]); // Update the maximum character seen
    p = mn + 1;          // Move past the selected character
    used[mn] = 1;        // Mark the character as used
  }
  for (int i = 0; i < s.size(); i++)
    if (!used[i] &&
        s[i] < mx) // Append unused characters smaller than max selected
      a.pb(s[i]);
  sort(a.begin(), a.end()); // Sort to get lexicographically smallest string
  for (int i = 0; i < a.size(); i++)
    cout << a[i];
  return 0;
}

// https://github.com/VaHiX/CodeForces/