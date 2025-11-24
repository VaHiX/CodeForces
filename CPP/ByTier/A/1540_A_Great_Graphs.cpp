// Problem: CF 1540 A - Great Graphs
// https://codeforces.com/contest/1540/problem/A

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
long long ans;
int d[100005];
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &d[i]);
    sort(d + 1, d + 1 + n); // Sort the distances to facilitate calculation
    ans = d[n]; // Initialize answer with the largest distance
    for (int i = 1; i <= n; ++i)
      ans += d[i] * (n + 1ll - i - i); // Accumulate weighted contributions
    printf("%lld\n", ans);
  }
}
/*
Flowerbox:
Problem: A. Great Graphs
Purpose: To compute the minimum possible cost of a directed graph with weighted edges that satisfies given shortest path distances from node 1 to all other nodes.

Algorithms/Techniques: Sorting, Greedy approach with mathematical optimization.

Time Complexity: O(n log n) per test case due to sorting, where n is the number of pastures.
Space Complexity: O(n) for storing the array d.

The solution works by:
1. Sorting distances in ascending order.
2. For each node i, compute contribution based on its position and the sorted distances.
3. Summing up these contributions gives the minimal total edge weight.
*/

// https://github.com/VaHiX/codeForces/