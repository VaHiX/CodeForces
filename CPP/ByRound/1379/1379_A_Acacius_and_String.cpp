// Problem: CF 1379 A - Acacius and String
// https://codeforces.com/contest/1379/problem/A

/*
Purpose: This code determines if a given string with question marks can be filled with lowercase letters 
         such that the substring "abacaba" occurs exactly once. It uses a brute-force approach to try 
         placing "abacaba" at each possible position and validating that exactly one occurrence exists.

Algorithms/Techniques: Brute-force with string matching and validation
Time Complexity: O(n^2) where n is the length of the input string (due to nested loops and string comparisons)
Space Complexity: O(n) for storing the input and result strings

The solution works by:
1. Trying to place "abacaba" at every possible starting index
2. Filling in the remaining characters with 'z' or keeping original if they are '?'
3. Validating that only one occurrence of "abacaba" exists
4. Returning the first valid configuration found or "No" if none exists
*/

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
int t, n, f, h, i;
char r[64], s[64], z[] = "abacaba";
int main() {
  for (scanf("%d", &t); t--;
       f == 1 ? printf("Yes\n%s\n", r) : printf("No\n"), f = 0)
    for (scanf("%d%s", &n, s), r[n] = 0, n = 6; s[n] && f != 1; ++n) {
      // Try placing "abacaba" at position n and check if it's valid
      for (h = 1, i = 0; i != 7;
           h &= s[n - i] == (r[n - i] = z[i]) || s[n - i] == '?', ++i)
        ;
      // Fill the rest of the string: if it's '?', fill with 'z', otherwise keep original
      for (i = 0; h && s[i];
           i + 6 < n || n < i ? r[i] = (s[i] == '?' ? 'z' : s[i]) : 0, ++i)
        ;
      // Count occurrences of "abacaba" in the constructed string
      for (f = i = 0; h && s[i]; f += !strncmp(r + i, z, 7), ++i)
        ;
    }
  return 0;
}


// https://github.com/VaHiX/CodeForces/