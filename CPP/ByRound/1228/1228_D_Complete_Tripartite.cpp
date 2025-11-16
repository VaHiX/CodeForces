// Problem: CF 1228 D - Complete Tripartite
// https://codeforces.com/contest/1228/problem/D

/*
D. Complete Tripartite
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
You have a simple undirected graph consisting of n vertices and m edges. The
graph doesn't contain self-loops, there is at most one edge between a pair of
vertices. The given graph can be disconnected. Let's make a definition. Let v1
and v2 be two some nonempty subsets of vertices that do not intersect. Let f(v1,
v2) be true if and only if all the conditions are satisfied:

 There are no edges with both endpoints in vertex set v1.
 There are no edges with both endpoints in vertex set v2.
 For every two vertices x and y such that x is in v1 and y is in v2, there is an
edge between x and y. Create three vertex sets (v1, v2, v3) which satisfy the
conditions below;

 All vertex sets should not be empty.
 Each vertex should be assigned to only one vertex set.
 f(v1, v2), f(v2, v3), f(v1, v3) are all true.
Is it possible to create such three vertex sets? If it's possible, print
matching vertex set for each vertex.

Algorithms/Techniques: Hashing with randomization to detect tripartite
structure; XOR-based approach for assigning vertices to classes. Time
Complexity: O(n + m) Space Complexity: O(n + m)
*/

#include <map>
#include <random>
#include <stdio.h>

using namespace std;
const int MAXA = 2e5;
#define ULL long long
int n, m, x, y, N,
    col[MAXA]; // Variables for reading input, tracking components and coloring
ULL a[MAXA],
    f[MAXA]; // a stores random hashes; f stores XOR of edges for each vertex
map<ULL, int> ma; // Map to store hash values to component IDs

int main() {
  scanf("%d%d", &n, &m); // Read number of vertices and edges
  for (int i = 1; i <= n; i++)
    a[i] = rand(); // Assign random hashes to each vertex
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y); // Read edge
    f[x] ^= a[y];          // XOR hash of neighbor with current vertex
    f[y] ^= a[x];          // XOR hash of neighbor with current vertex
  }
  for (int i = 1; i <= n; i++) {
    if (!f[i]) // If no edges exist for this vertex, return -1
      return printf("-1"), 0;
    x = ma[f[i]]; // Try to find existing component ID for hash of this vertex
    if (!x) {     // If not found, create new component
      x = ++N;    // Increment component counter
      if (x > 3)  // If more than three components, return -1
        return printf("-1"), 0;
      ma[f[i]] = x; // Register hash to component ID
    }
    col[i] = x; // Assign component ID to vertex
  }
  if (N < 3) // If less than three components assigned, return -1
    return printf("-1"), 0;
  for (int i = 1; i <= n; i++)
    printf("%d ", col[i]); // Output coloring of vertices
}

// https://github.com/VaHiX/codeForces/