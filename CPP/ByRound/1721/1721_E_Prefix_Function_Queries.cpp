// Problem: CF 1721 E - Prefix Function Queries
// https://codeforces.com/contest/1721/problem/E

/*
Algorithm: KMP (Knuth-Morris-Pratt) Prefix Function with Optimized State Transition
Time Complexity: O(|s| + sum(|t|)) for all queries combined
Space Complexity: O(|s| + 26) = O(|s|) for the automaton table and prefix function array

This code implements an optimized version of the KMP prefix function calculation.
It uses an automaton table `h` to store the state transitions for each character,
enabling efficient computation of prefix function values during query processing.
The algorithm avoids recomputing the entire prefix function from scratch for
each query by maintaining internal state transitions.
*/

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
const int N = 1e6 + 50;
int nxt[N], Q, h[N][26];
char s[N];
int main() {
  scanf("%s%d", s + 1, &Q);
  int n = strlen(s + 1), m;
  // Build the prefix function and automaton for string s
  for (int i = 2, j = 0; i <= n; i++) {
    j = h[j][s[i] - 'a'];  // Transition based on automaton table
    if (s[j + 1] == s[i])  // If characters match, extend the match
      j++;
    nxt[i] = j;            // Store prefix function value
    memcpy(h[j], h[nxt[j]], sizeof(h[j]));  // Copy state from previous prefix
    h[j][s[j + 1] - 'a'] = j;  // Update automaton to point to current state
  }
  while (Q--) {
    scanf("%s", s + n + 1);   // Read new string t
    m = strlen(s + n + 1) + n; // Calculate combined length
    // Process the concatenation s + t using the prefix function and automaton
    for (int i = n + 1, j = nxt[n]; i <= m; i++) {
      j = h[j][s[i] - 'a'];   // Transition using automaton
      if (s[j + 1] == s[i])   // If characters match, extend the match
        j++;
      nxt[i] = j;             // Store prefix function value
      memcpy(h[j], h[nxt[j]], sizeof(h[j]));  // Update automaton state
      h[j][s[j + 1] - 'a'] = j;  // Update automaton table
      printf("%d ", j);       // Output prefix function value for current position
    }
    puts("");  // Print newline after each query
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/