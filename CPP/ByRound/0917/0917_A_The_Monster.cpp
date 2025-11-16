// Problem: CF 917 A - The Monster
// https://codeforces.com/contest/917/problem/A

/*
 * Problem: Count the number of "pretty" substrings in a string of parentheses and question marks.
 * A "pretty" substring is one that can be transformed into a valid (non-empty) bracket sequence
 * by replacing each '?' with either '(' or ')'.
 *
 * Approach:
 * - For each starting position i, iterate through all possible ending positions j.
 * - Maintain counters `l` and `r` to simulate how many unmatched opening and closing brackets we have.
 *   - `l` tracks excess opening brackets
 *   - `r` tracks excess closing brackets
 * - When encountering '?', we assume it can be matched to balance the sequence (greedy strategy).
 * - If at any point `l < 0`, we set it to 1 because we cannot have negative unmatched open brackets.
 * - If `r < 0`, we break early since even if we flip all remaining '?' to ')' it's invalid.
 * - If `l == 0`, then current window is a valid pretty substring.
 *
 * Time Complexity: O(n^2) where n is the length of the string
 * Space Complexity: O(1) additional space excluding input
 */
#include <cstdio>
#include <cstring>
char s[5050];
int main() {
  scanf("%s", s);
  int i, j, l, r, n, ans = 0;
  n = strlen(s);
  for (i = 0; i < n; i++) {
    l = 0, r = 0;
    for (j = i; j < n; j++) {
      // Increment or decrement l based on character
      (s[j] == '(' ? l++ : l--);
      // Increment or decrement r based on character
      (s[j] == ')' ? r-- : r++);
      // If l becomes negative, it means we have more closing than opening brackets so far
      // We reset l to 1 to indicate that the next opening bracket would help us recover
      if (l < 0)
        l = 1;
      // If r becomes negative, then even if we use all remaining '?' as ')', we're still imbalanced
      // So this substring cannot be pretty
      if (r < 0)
        break;
      // If l equals 0, it's a valid and complete bracket sequence
      if (l == 0)
        ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/