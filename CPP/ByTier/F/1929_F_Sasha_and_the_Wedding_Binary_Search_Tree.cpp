// Problem: CF 1929 F - Sasha and the Wedding Binary Search Tree
// https://codeforces.com/contest/1929/problem/F

/*
 * Problem: Sasha and the Wedding Binary Search Tree
 *
 * Purpose:
 *   This code computes the number of valid binary search trees (BSTs) that can be formed
 *   given a partial BST structure with some unknown node values, where node values are
 *   constrained to [1, C]. It uses DFS traversal to process the tree and calculates
 *   combinations based on constraints from the BST property.
 *
 * Algorithm:
 *   - Perform DFS traversal on the BST to determine the order of nodes.
 *   - For each known node value, calculate how many combinations are possible
 *     between it and the previously seen node, considering the BST property.
 *   - Multiply the result by the number of choices left for unknowns.
 *
 * Time Complexity:
 *   O(N + log(C)) per test case, where N is the number of nodes.
 *   The precomputation of modular inverses is O(C), and DFS is O(N).
 *
 * Space Complexity:
 *   O(N) for storing tree structure and auxiliary arrays.
 */

#include <stdio.h>

char *buffer = new char[5 << 21];
inline int read() {
  int x = 0;
  while (*buffer < '-')
    buffer++;
  if (*buffer == '-')
    return buffer += 3, 0;
  do
    x = x * 10 + (*buffer++ ^ '0');
  while (*buffer >= '0');
  return x;
}
constexpr int mod = 998244353, N = 5e5 + 5;
int l[N], r[N], v[N], inv[N];  // l, r: left/right child; v: node value; inv: modular inverse array
int last, lastpos, pos;        // last: previous node value; lastpos: position of last node; pos: current position
long long ans;                 // final answer
void dfs(int u) {
  if (l[u])                   // if left child exists, traverse it
    dfs(l[u]);
  pos++;                      // increment current position
  if (v[u]) {                 // if current node value is known
    if (pos != lastpos + 1)   // if we are skipping positions (i.e., there are unknown values)
      for (int i = 1; i <= pos - lastpos - 1; i++)  // calculate combinations for unknowns
        ans = ans * (v[u] - last + i) % mod * inv[i] % mod;
    last = v[u], lastpos = pos;  // update last seen value and position
  }
  if (r[u])                   // if right child exists, traverse it
    dfs(r[u]);
}
int main() {
  inv[1] = 1;                 // precompute modular inverse for 1
  for (int i = 2; i < N; i++) // precompute modular inverses using Fermat's little theorem
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
  fread(buffer, 1, 5 << 21, stdin);
  int T = read();             // number of test cases
  while (T--) {
    int n = read(), c = read();  // read number of nodes and max value C
    for (int i = 1; i <= n; i++)
      l[i] = read(), r[i] = read(), v[i] = read();  // read tree structure
    ans = last = 1, lastpos = pos = -1, dfs(1);   // reset and start DFS from root
    for (int i = 1; i <= n - lastpos - 1; i++)    // handle remaining unknowns
      ans = ans * (c - last + i) % mod * inv[i] % mod;
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/