// Problem: CF 916 C - Jamie and Interesting Graph
// https://codeforces.com/contest/916/problem/C

/*
Code Purpose:
This program constructs a connected undirected weighted graph with n vertices and m edges that satisfies the following conditions:
1. The shortest path from vertex 1 to vertex n has a prime weight.
2. The sum of the weights in the Minimum Spanning Tree (MST) of the graph is also a prime number.
The algorithm uses a linear chain from 1 to n with small weights (1) to ensure the shortest path is a prime,
then adds extra edges with large weights to satisfy the number of edges constraint without altering the MST.

Algorithms/Techniques:
- Graph Construction: Uses a path from 1 to n with unit weights and appends edges to meet m edge count.
- Primality: Uses a fixed prime (100003) for both shortest path and MST sum.

Time Complexity: O(n^2) due to nested loops for adding extra edges.
Space Complexity: O(1) - constant extra space excluding input/output.

*/
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100
#define inf 100000
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int p = 100003, x = 10000000;  // p is a prime number used for shortest path and MST weight; x is a large weight for extra edges
  cin >> n >> m;
  cout << p << " " << p << endl;  // Output the prime numbers for shortest path and MST sum

  // Create a path from 1 to n with weights 1 so that shortest path from 1 to n is (n-1) which is not prime,
  // but we will adjust last edge to make total path weight a prime (100003)
  for (i = 1; i <= n - 2; i++) {
    cout << i << " " << (i + 1) << " 1" << endl;
    p--;  // Reduce p to keep path sum correct for end
  }
  cout << (n - 1) << " " << (n) << " " << p << endl;  // Last edge makes total path weight equal to prime p
  m -= (n - 1);  // Reduce m by number of edges in path

  // Add remaining edges with large weights to satisfy total edge count
  for (i = 1; i < n - 1; i++) {
    for (j = i + 1; j <= n; j++) {
      if (i + 1 == j)
        continue;  // Skip if it's part of the path already
      if (!m)
        return 0;  // Stop if we've added all required edges
      cout << i << " " << j << " " << x << endl;  // Add edge with large weight
      m--;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/