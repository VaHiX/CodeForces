// Problem: CF 1669 E - 2-Letter Strings
// https://codeforces.com/contest/1669/problem/E

/*
Algorithm: 
- For each string, we generate all possible strings that differ by exactly one character.
- We use a map to store all indices of each string for fast lookup.
- For every string, we iterate through each of its positions and try replacing the character with all possible characters from 'a' to 'k'.
- If the modified string exists in the map, we count how many of its indices are greater than the current index (to ensure i < j).
- This is done using upper_bound to efficiently find the first index greater than i+1.

Time Complexity: O(n * 2 * 26 * log(n)) = O(n * log(n)), where n is the number of strings.
Space Complexity: O(n * 2) = O(n), for storing strings and the map.

Techniques:
- Map for fast string to index list lookup.
- Binary search (upper_bound) to count valid pairs efficiently.
- Two nested loops to try all character replacements at each position.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define nl printf("\n")
#define N 10101
#define inf 1e9
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
int main() {
  int i, j, k;
  int n, m, t;
  cin >> t;
  while (t--) {
    cin >> n;
    string s[n], temp;
    map<string, vector<int>> index; // Map to store string to list of indices
    for (i = 0; i < n; i++)
      cin >> s[i], index[s[i]].push_back(i + 1); // Store each string with its 1-based index
    ll ans = 0; // Final answer
    for (i = 0; i < n; i++) {
      temp = s[i];
      // Try changing the second character of the string
      for (char ch = 'a'; ch <= 'k'; ch++) {
        if (ch == s[i][1]) // Skip if same character
          continue;
        temp[1] = ch;
        if (index.find(temp) != index.end()) { // If such string exists
          j = upper_bound(index[temp].begin(), index[temp].end(), i + 1) -
              index[temp].begin(); // Find first index > i+1
          ans += index[temp].size() - j; // Add number of valid pairs
        }
      }
      temp = s[i];
      // Try changing the first character of the string
      for (char ch = 'a'; ch <= 'k'; ch++) {
        if (ch == s[i][0]) // Skip if same character
          continue;
        temp[0] = ch;
        if (index.find(temp) != index.end()) { // If such string exists
          j = upper_bound(index[temp].begin(), index[temp].end(), i + 1) -
              index[temp].begin(); // Find first index > i+1
          ans += index[temp].size() - j; // Add number of valid pairs
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/