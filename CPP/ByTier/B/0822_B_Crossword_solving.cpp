// Problem: CF 822 B - Crossword solving
// https://codeforces.com/contest/822/problem/B

/*
 * Task: Find minimal number of characters to replace in string 's' 
 *       so that 's' becomes a substring of 't'. 
 *       '?' in 's' can match any character.
 *
 * Algorithm:
 *   1. Try all possible alignments of 's' in 't' (O(n - m + 1) alignments).
 *   2. For each alignment, count how many characters need to be replaced (O(m)).
 *   3. Keep track of the alignment with minimum replacements.
 *   4. Output the positions of characters to be replaced.
 *
 * Time Complexity: O((n - m + 1) * m) = O(n * m)
 * Space Complexity: O(1) - only using a few variables and input strings
 */

#include <iostream>
#include <string>

using namespace std;
int n, m, a = 2e9, ai, j, c, i;
string s, t;
int main() {
  cin >> m >> n >> s >> t; // Read m, n, s, t
  for (i = 0; i <= n - m; i++) { // Try each possible starting position in t
    for (j = c = 0; j < m; j++) // Count mismatches for current alignment
      t[i + j] != s[j] ? c++ : 0; // Increment counter if characters don't match
    c < a ? a = c, ai = i : 0; // Update minimum mismatches and alignment index
  }
  cout << a << " "; // Print minimal number of replacements
  for (j = 0; j < m; j++) // Identify positions to change
    t[ai + j] != s[j] ? cout << j + 1 << " ", 0 : 0; // Output position if mismatch
  return 0;
}


// https://github.com/VaHiX/CodeForces/