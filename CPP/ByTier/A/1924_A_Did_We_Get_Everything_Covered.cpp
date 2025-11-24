// Problem: CF 1924 A - Did We Get Everything Covered?
// https://codeforces.com/contest/1924/problem/A

/*
Purpose: This code determines whether all possible strings of length n
         formed using the first k lowercase letters appear as subsequences in the input string s.
         If not, it outputs one such missing string.

Algorithms/Techniques:
- Bit manipulation to track which characters have been seen
- Greedy approach to construct a missing subsequence

Time Complexity: O(m) per test case where m is the length of input string s.
Space Complexity: O(n) for the output string s2.

The key idea is to scan the string s and track which of the first k letters have been seen.
Each time all k letters have been seen, we "reset" and record the last character we saw.
If we've seen at least n characters in this way, then all subsequences of length n exist.
Otherwise, we construct a missing string by checking which letter from the first k is missing
and then padding with 'a's.
*/

#include <cstdio>
const int N = 100002;
int T, n, k, m, i, j, p, x;
char s[N], s2[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%s", &n, &k, &m, s + 1);
    p = x = 0;
    for (i = 1; i <= m; i++) {
      p |= 1 << (s[i] - 'a');  // Mark character s[i] as seen using bit manipulation
      if (p == (1 << k) - 1) { // If all k characters have been seen
        p = 0;               // Reset the set of seen characters
        s2[++x] = s[i];      // Record the last character seen in this segment
      }
    }
    if (x >= n)
      printf("YES\n");
    else {
      printf("NO\n");
      for (i = 0; i < k; i++)
        if ((p & 1 << i) == 0) {  // Find first missing character
          s2[++x] = i + 'a';
          break;
        }
      while (x < n)
        s2[++x] = 'a';  // Pad with 'a's to form a length-n string
      s2[x + 1] = 0;
      printf("%s\n", s2 + 1);
    }
  }
}


// https://github.com/VaHiX/CodeForces/