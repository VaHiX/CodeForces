// Problem: CF 494 A - Treasure
// https://codeforces.com/contest/494/problem/A

/*
 * Treasure Problem Solution
 *
 * Algorithm:
 * - Greedily assign ')' to '#' characters to make the string beautiful.
 * - A beautiful string satisfies two conditions:
 *   1. At any prefix, number of ')' should not exceed number of '('.
 *   2. Total count of '(' equals total count of ')'.
 *
 * Approach:
 * - First pass: scan from left to right to determine how many ')' we need to add
 *   to make the string valid. If at any point the balance (open - close) goes negative,
 *   it's impossible.
 * - Track the last '#' character to know where to start placing extra ')' at the end.
 * - Second pass: from the last '#' to end, compute how many ')' we are missing from the
 *   remaining part.
 * - Distribute 1 ')' to all '#' except the last one, and assign the rest to the last one.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
char s[100005];
int n, k, cnt, m, t, tot;

int main() {
  scanf("%s", s);
  n = strlen(s);
  
  // First pass: check validity and count necessary values
  for (int i = 0; i < n; i++) {
    if (s[i] == '(')
      k++;  // increment open count
    if (s[i] == ')')
      k--;  // decrement open count
    if (s[i] == '#')
      cnt++, k--, t = i;  // count # and adjust k as if we already placed one ')' in it
    if (k < 0) {
      puts("-1");
      return 0;
    }
  }
  
  // Second pass: evaluate remaining part after the last '#'
  for (int i = t + 1; i <= n; i++) {
    if (s[i] == '(')
      tot++;
    if (s[i] == ')')
      tot--;
    tot = max(tot, 0);  // keep track of minimum required deficit
  }
  
  // Check if balance can be resolved
  if (tot > 0) {
    puts("-1");
    return 0;
  }
  
  // Output the number of ')' to assign to each #
  for (int i = 1; i < cnt; i++)
    puts("1");
  printf("%d", k + 1);
  return 0;
}


// https://github.com/VaHiX/CodeForces/