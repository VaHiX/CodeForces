// Problem: CF 670 E - Correct Bracket Sequence Editor
// https://codeforces.com/contest/670/problem/E

/*
 * Correct Bracket Sequence Editor
 *
 * Algorithm/Techniques:
 * - Bracket matching using a stack to precompute matching brackets
 * - Maintain a doubly linked list to efficiently delete segments
 * - Use pointers to simulate the cursor movement and deletion operations
 *
 * Time Complexity: O(n + m)
 *   - Preprocessing (matching brackets): O(n)
 *   - Operations: O(m)
 *   - Output: O(n)
 *
 * Space Complexity: O(n)
 *   - Storage for string, match array, and linked list pointers
 */

#include <stdio.h>
#include <utility>

using namespace std;
const int N = 500007;
int n, m, p, t;
char s[N], op[N];
int l[N + 1], r[N + 1];        // left and right pointers for doubly linked list
int match[N], stk[N], top = 0; // match array and stack for bracket pairing
int main() {
  scanf("%d%d%d", &n, &m, &p);
  scanf("%s", s + 1);
  r[0] = 1;  // Initialize right pointer of dummy node 0
  for (int i = 1; i <= n; i++) {
    l[i] = i - 1;           // Left pointer points to previous bracket
    if (i == n)
      r[i] = N;             // Right pointer of last bracket points to dummy node
    else
      r[i] = i + 1;         // Right pointer points to next bracket
  }
  l[N] = n;                 // Left pointer of dummy node points to last bracket
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(')
      stk[++top] = i;       // Push index of '(' onto stack
    else {
      match[i] = stk[top];  // Match closing bracket to opening bracket
      match[stk[top]] = i;  // Match opening bracket to closing bracket
      --top;                // Pop from stack
    }
  }
  scanf("%s", op);
  for (int i = 0; i < m; i++) {
    if (op[i] == 'L')
      p = l[p];             // Move cursor left using left pointer
    else if (op[i] == 'R')
      p = r[p];             // Move cursor right using right pointer
    else {
      int q = match[p];     // Find matching bracket
      if (p > q)
        swap(p, q);         // Ensure p is smaller, so p is the start bracket
      r[l[p]] = r[q];       // Update right pointer of bracket before p
      l[r[q]] = l[p];       // Update left pointer of bracket after q
      if (r[q] != N)        // If there is a bracket to the right of q
        p = r[q];           // Move cursor to the right
      else
        p = l[p];           // Otherwise move cursor to the left
    }
  }
  for (int i = r[0]; i != N; i = r[i]) {  // Traverse the linked list from beginning
    putchar(s[i]);                        // Print each remaining bracket
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/