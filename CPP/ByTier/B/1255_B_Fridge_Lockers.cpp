// Problem: CF 1255 B - Fridge Lockers
// https://codeforces.com/contest/1255/problem/B

/*
Code Purpose:
This program solves the problem of connecting fridges in a shared apartment such that:
1. Exactly m steel chains are created.
2. All fridges are private (only the owner can open them).
3. The total cost of chains is minimized.

The approach is based on constructing a cycle graph with n nodes (fridges) and n edges.
This ensures that:
- Each fridge has exactly 2 chains connected to it.
- No two people can open a fridge together (since each fridge is only connected to two others in a cycle).
- Total cost = 2 * sum of all fridge weights (since for each edge we pay the sum of weights of the two fridges it connects).
- The number of edges must be at least n to form a valid cycle, and m must equal n for a solution to exist.

Time Complexity: O(n) per test case - we read input and print output linearly.
Space Complexity: O(1) - only using a few variables regardless of input size.

Algorithms/Techniques: Graph theory (cycle construction), Greedy approach for minimizing cost.
*/
#include <stdio.h>
#include <iosfwd>

using namespace std;
int work() {
  int n, m, sum = 0, x;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &x), sum += x;
  // If n < 3 or m < n, it's impossible to create a valid solution.
  if (n < 3 || m < n)
    return puts("-1"), 0;
  // The minimal cost is twice the sum of all weights (each edge connects two fridges).
  printf("%d\n", sum * 2);
  // Construct a cycle: each fridge i connects to fridge (i % n + 1).
  for (int i = 1; i <= n; i++)
    printf("%d %d\n", i, i % n + 1);
  return 0;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/