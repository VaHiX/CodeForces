// Problem: CF 1620 E - Replace the Numbers
// https://codeforces.com/contest/1620/problem/E

/*
Algorithm: Union-Find (Disjoint Set Union) with Reverse Processing
Time Complexity: O(q * α(q)) where α is the inverse Ackermann function, nearly constant
Space Complexity: O(max_value) where max_value is up to 5*10^5

This solution processes queries in reverse order to efficiently track value replacements.
It uses a union-find like structure 'to' to map each value to its final replacement.
When a "1 x" query is processed, we record the value after all replacements.
When a "2 x y" query is processed, we update the mapping to redirect x to point to y.
*/

#include <cstdio>
int n, i, to[500001], x[500001], y[500001], z[500001], a[500001];
int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    if (x[i] == 2)  // If it's a replacement query, read the third value
      scanf("%d", &z[i]);
  }
  for (i = 1; i <= 500000; i++)
    to[i] = i;  // Initialize the mapping: each number maps to itself
  for (i = n; i >= 1; i--)  // Process queries in reverse order
    if (x[i] == 1)  // If it's an add query, store the value after all replacements
      a[i] = to[y[i]];
    else  // If it's a replace query, update the mapping
      to[y[i]] = to[z[i]];
  for (i = 1; i <= n; i++)  // Output all added values
    if (a[i])
      printf("%d ", a[i]);
}


// https://github.com/VaHiX/CodeForces/