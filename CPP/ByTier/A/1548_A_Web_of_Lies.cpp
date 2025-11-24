// Problem: CF 1548 A - Web of Lies
// https://codeforces.com/contest/1548/problem/A

/*
 * Problem: A. Web of Lies
 *
 * Purpose: Simulate a graph-based process where nobles (nodes) are vulnerable if all their friends have higher power,
 * and they get eliminated along with their edges until no more are vulnerable. This simulates a kind of "collapse" in the graph.
 *
 * Algorithm/Techniques:
 * - Use an array `x` to track the degree of each node (number of friends)
 * - Track `tot`, the number of nobles remaining that are not yet eliminated
 * - For each query:
 *   - Type 1: Add edge, increment degree of one endpoint; if it became 1 (wasn't vulnerable before), decrease `tot`
 *   - Type 2: Remove edge, decrement degree; if becomes 0 (now vulnerable again), increase `tot`
 *   - Type 3: Output current value of `tot` representing remaining nobles after full elimination process
 *
 * Time Complexity:
 *   Adding/removing edges: O(1) per operation
 *   Process in type 3 queries: Since we only perform decrement/increment on total count (`tot`) as degrees change,
 *                              and each node can be added/removed from vulnerable list at most once, this is effectively
 *                              bounded by the number of operations. Worst-case linear with respect to operations.
 *
 * Space Complexity:
 *   O(n) - for storing degrees and other variables up to 2*10^5
 */

#include <stdio.h>
int x[200010]; // Array to store degree (number of friends) for each noble
int main() {
  int n, m, tot;
  scanf("%d%d", &n, &m);
  int a, b, k;
  tot = n; // Initially all nobles are alive
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a, &b);
    if (a > b)
      k = a, a = b, b = k; // Make sure 'a' is smaller to keep consistent indexing (not really required but helps in logic)
    x[a]++; // Increment degree of node 'a'
    if (x[a] == 1) // If first edge was added, this noble becomes non-vulnerable
      tot--; // Reduce count of nobles that are potentially vulnerable
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int f;
    scanf("%d", &f);
    if (f == 1) { // Add friendship
      scanf("%d%d", &a, &b);
      if (a > b)
        k = a, a = b, b = k;
      x[a]++;
      if (x[a] == 1) // Was not vulnerable before; now becomes part of graph and may be eliminated later
        tot--;
    }
    if (f == 2) { // Remove friendship
      scanf("%d%d", &a, &b);
      if (a > b)
        k = a, a = b, b = k;
      x[a]--;
      if (x[a] == 0) // Now no friends; possible candidate for vulnerability
        tot++;
    }
    if (f == 3)
      printf("%d\n", tot); // Report current number of remaining nobles after collapsing process
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/