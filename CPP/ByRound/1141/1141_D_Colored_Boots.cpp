// Problem: CF 1141 D - Colored Boots
// https://codeforces.com/contest/1141/problem/D

/*
Algorithm: Greedy Matching with Question Marks
Time Complexity: O(n)
Space Complexity: O(n)

The approach uses a greedy strategy to form pairs of boots:
1. First, match specific colors between left and right boots.
2. Then, use question marks on the left side to match with specific colors on the right.
3. Next, use question marks on the right side to match with specific colors on the left.
4. Finally, match remaining question marks with each other.

The algorithm maintains separate vectors for each color (including a special vector for '?') to track indices of boots.
It greedily forms pairs prioritizing exact matches over using question marks, maximizing the total number of compatible pairs.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 2500
#define inf 1e6
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
vector<int> S[27]; // Stores indices of left boots for each color (26 colors + 1 for '?')
vector<int> T[27]; // Stores indices of right boots for each color (26 colors + 1 for '?')
int main() {
  int i, j, k;
  int n, m;
  string s, t;
  sf(n);
  cin >> s >> t;
  vector<pp> ans; // Stores the resulting pairs
  map<int, int> ms, mt; // Count of each character in left and right strings
  for (i = 0; i < n; i++) {
    // Store indices of left boots by color
    if (s[i] != '?')
      S[s[i] - 'a'].pb(i + 1);
    else
      S[26].pb(i + 1);
    // Store indices of right boots by color
    if (t[i] != '?')
      T[t[i] - 'a'].pb(i + 1);
    else
      T[26].pb(i + 1);
    // Count characters
    ms[s[i]]++;
    mt[t[i]]++;
  }
  // Match specific colors from left boot to right boot
  for (i = 0; i < n; i++) {
    if (s[i] == '?')
      continue;
    if (mt[s[i]]) { // If there's a matching color in right boot
      ms[s[i]]--; // Reduce count
      mt[s[i]]--;
      ans.pb({S[s[i] - 'a'].back(), T[s[i] - 'a'].back()});
      T[s[i] - 'a'].pop_back(); // Remove last index used
      S[s[i] - 'a'].pop_back();
    }
  }
  // Use left '?', match with specific right colors
  for (i = 0; i < n; i++) {
    if (t[i] == '?')
      continue;
    if (mt[t[i]] && ms['?']) { // If right boot has color and left boot has '?'
      ms['?']--;
      mt[t[i]]--;
      ans.pb({S[26].back(), T[t[i] - 'a'].back()});
      S[26].pop_back();
      T[t[i] - 'a'].pop_back();
    }
  }
  // Use right '?', match with specific left colors
  for (i = 0; i < n; i++) {
    if (s[i] == '?')
      continue;
    if (ms[s[i]] && mt['?']) { // If left boot has color and right boot has '?'
      mt['?']--;
      ms[s[i]]--;
      ans.pb({S[s[i] - 'a'].back(), T[26].back()});
      T[26].pop_back();
      S[s[i] - 'a'].pop_back();
    }
  }
  // Pair leftover '?'
  while (S[26].size() && T[26].size()) {
    ans.pb({S[26].back(), T[26].back()});
    S[26].pop_back();
    T[26].pop_back();
  }
  pf(ans.size());
  nl;
  m = ans.size();
  for (i = 0; i < m; i++)
    pff(ans[i].first, ans[i].second), nl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/