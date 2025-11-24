// Problem: CF 2010 C2 - Message Transmission Error (hard version)
// https://codeforces.com/contest/2010/problem/C2

/*
C2. Message Transmission Error (hard version)
Algorithm: KMP (Knuth-Morris-Pratt) preprocessing to find longest proper prefix which is also suffix.
Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(n), for storing the 'nxt' array and the input string.

The problem is about detecting if a given string can be split into two identical substrings
that overlap at their ends. This is essentially finding whether the string has a repeat pattern
with overlapping parts, such that one copy of the string overlaps with another.
This is solved using KMP failure function (also known as 'nxt' array) to find the longest proper prefix
which is also a suffix of the entire string. If this length satisfies specific conditions,
we can reconstruct the base message.

The key checks:
1. If the longest repeating suffix-prefix length is <= n/2, then no valid overlap exists.
2. Otherwise, that length represents the size of the original message.

*/

#include <iosfwd>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, nxt[400100];  // nxt[i] stores the longest proper prefix of s[1..i] which is also a suffix
char a[400100];
int main() {
  scanf("%s", a + 1);  // Read input starting from index 1
  n = strlen(a + 1);
  nxt[1] = 0;  // Base case: prefix of length 1 has no proper prefix
  for (int i = 2, j = 0; i <= n; i++) {
    // While current character does not match and j > 0, fall back to previous match
    while (j && a[j + 1] != a[i])
      j = nxt[j];
    // If characters match, extend the matching length
    if (a[j + 1] == a[i])
      j++;
    nxt[i] = j;  // Store the longest prefix-suffix match for current position
  }
  // Check if valid repeat pattern exists and is not full overlap
  if (nxt[n] * 2 <= n)
    printf("NO");
  else {
    printf("YES\n");
    for (int i = 1; i <= nxt[n]; i++)
      printf("%c", a[i]);  // Print the base message
  }
}


// https://github.com/VaHiX/codeForces/