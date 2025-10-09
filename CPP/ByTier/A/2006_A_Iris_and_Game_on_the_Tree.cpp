// Problem: CF 2006 A - Iris and Game on the Tree
// https://codeforces.com/contest/2006/problem/A

/*
A. Iris and Game on the Tree
Problem Description:
Given a tree rooted at vertex 1, each node has a value (0, 1, or ?). For each leaf of the tree,
we compute a string by traversing from root to that leaf. The weight of a leaf is defined as 
the difference between number of "10" and "01" substrings in its string.
The score of the tree is the number of leaves with non-zero weight.
Some node values are '?', and two players (Iris and Dora) alternately assign 0 or 1 to these nodes.
Iris plays first and wants to maximize the score, while Dora wants to minimize it.
Both play optimally.

Algorithms/Techniques:
- Tree traversal and leaf detection
- Greedy strategy for optimal play on ? vertices
- Counting of leaves with specific degrees (1) and character values

Time Complexity: O(N) per test case where N is the number of nodes
Space Complexity: O(N) for storing tree structure and auxiliary arrays
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 100005;
int T, n, C[N]; // C[i] stores degree of vertex i
char s[N];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      C[i] = 0;
    for (int i = 1; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      C[u]++, C[v]++; // Increment degrees of both nodes
    }
    scanf("%s", s + 1); // Read string of values (1-indexed)
    int cnt = 0;
    for (int i = 2; i <= n; i++) // Count ? characters (excluding root)
      if (s[i] == '?')
        cnt++;
    
    int c0 = 0, c1 = 0, c2 = 0; // Count leaf nodes with values '0', '1', '?' respectively
    for (int i = 2; i <= n; i++) {
      if (C[i] != 1) // If vertex is not a leaf, skip
        continue;
      if (s[i] == '0')
        c0++;
      else if (s[i] == '1')
        c1++;
      else
        c2++; // '?' node
    }
    
    // Decision logic for optimal play:
    // Case 1: Root is '0'
    if (s[1] == '0')
      printf("%d\n", (c2 + 1) / 2 + c1);
    // Case 2: Root is '1'
    else if (s[1] == '1')
      printf("%d\n", (c2 + 1) / 2 + c0);
    // Case 3: Root is '?', depends on leaf counts
    else if (c0 != c1)
      printf("%d\n", c2 / 2 + max(c0, c1));
    else
      printf("%d\n", (c2 + ((cnt - c2) & 1)) / 2 + c0);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/