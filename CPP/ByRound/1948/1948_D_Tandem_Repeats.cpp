// Problem: CF 1948 D - Tandem Repeats?
// https://codeforces.com/contest/1948/problem/D

/*
Algorithm: Tandem Repeat Detection
Techniques: 
- Sliding window approach with length-based iteration
- Character-by-character comparison with wildcard handling
- Reverse iteration from maximum possible tandem repeat length down to 1

Time Complexity: O(n^3), where n is the length of the string. In worst case, we iterate over all possible tandem repeat lengths (n/2), and for each, we perform O(n) comparisons.
Space Complexity: O(1), no extra space used apart from variables.

The solution checks for the longest possible tandem repeat substring by:
1. Iterating from the largest possible length down to 1,
2. For each length, checking all possible tandem repeats of that length,
3. Using a helper function to compare characters (handling ? as wildcards),
4. Returning the first valid length found, which will be the maximum due to reverse iteration.
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
constexpr int M = 5005;
int n;
string s;
bool check(char a, char b) { return a == b || a == '?' || b == '?'; }
void solve() {
  cin >> s;
  n = s.length();
  s = " " + s; // Add padding to make indexing easier (1-based)
  for (int i = n >> 1; i; i--) // Iterate from half the length down to 1
    for (int j = i, k = i << 1; k <= n; j += i, k += i) { // Check all tandem repeats of length 2*i
      int lcs = 0, lcp = 0; // lcs: longest common suffix, lcp: longest common prefix
      for (int r = 1; r < i; r++) // Compare from end of first half to start
        if (check(s[j - r], s[k - r]))
          lcs = r;
        else
          break;
      for (int r = 1; r <= i && k + r - 1 <= n; r++) // Compare from start of second half
        if (check(s[j + r - 1], s[k + r - 1]))
          lcp = r;
        else
          break;
      if (lcs + lcp >= i) // If combined match is at least the length of half the tandem repeat
        return printf("%d\n", i << 1), void(); // Return double the half length
    }
  puts("0"); // No tandem repeat found
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/