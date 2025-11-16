// Problem: CF 1763 E - Node Pairs
// https://codeforces.com/contest/1763/problem/E

/*
Algorithm: Dynamic Programming
Time Complexity: O(n * sqrt(n))
Space Complexity: O(n)

The problem is about finding the minimum number of nodes to form a p-reachable graph,
and among all such graphs with minimum nodes, finding the maximum number of unidirectional pairs.

Key insight:
- A p-reachable graph has exactly p ordered pairs (u, v) where u < v and u and v are mutually reachable.
- We can think of this as representing a number p as a sum of triangular numbers (1, 3, 6, 10, ...),
  where each triangular number T_i = i*(i-1)/2 corresponds to a component of the graph.
- The minimum number of nodes is the minimum number of terms needed to represent p.
- Once we know the minimum number of nodes k, the maximum number of unidirectional pairs is
  the total possible pairs in k nodes minus p (the pairs that are mutual).

Approach:
1. Use dynamic programming to compute the minimum number of components (triangular numbers) needed to form p.
2. For each triangular number T_i = i*(i-1)/2, we can add i nodes.
3. The answer is f[n] (minimum number of nodes) and f[n] * (f[n] - 1) / 2 - n (unidirectional pairs).
*/

#include <string.h>
#include <iostream>

using namespace std;
int f[1000001];
int main() {
  long long n, x;
  cin >> n;
  memset(f, 0x3f, sizeof(f));  // Initialize dp array with a large value
  f[0] = 0;  // Base case: 0 nodes needed to make 0 pairs
  for (int j = 1; j <= n; ++j)  // For each target number of pairs
    for (int i = 1; i * (i - 1) / 2 <= j; ++i)  // Try all triangular numbers
      if (f[j] >= f[j - i * (i - 1) / 2] + i)  // If using current triangular number reduces node count
        f[j] = f[j - i * (i - 1) / 2] + i;  // Update minimum node count
  cout << f[n] << ' ' << f[n] * (f[n] - 1) / 2 - n;  // Output min nodes and max unidirectional pairs
}


// https://github.com/VaHiX/CodeForces/