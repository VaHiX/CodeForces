// Problem: CF 504 A - Misha and Forest
// https://codeforces.com/contest/504/problem/A

/*
 * Problem: Misha and Forest
 * 
 * Purpose: 
 *   Given a forest (a collection of trees) with n vertices, each vertex has two values:
 *   - degree[i]: the number of adjacent vertices
 *   - s[i]: the XOR sum of adjacent vertex indices
 *   We need to reconstruct the original edges of the forest.
 *   
 * Algorithm:
 *   This solution uses a BFS-like approach with a queue to process vertices with degree 1.
 *   When a vertex has degree 1, we infer that it connects to exactly one other vertex.
 *   The XOR sum s[i] must then be the index of that neighbor.
 *   We connect them and update the neighbor's degree and its XOR sum accordingly.
 *   We repeat until all edges are determined.
 *   
 * Time Complexity: O(n)
 *   - Each vertex is processed at most once.
 *   - Each edge is added once to the result.
 *   
 * Space Complexity: O(n)
 *   - Storage for degree, s, ex, ey arrays and the queue.
 */

#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;
typedef long long ll;
const int maxn = 2e6 + 5;
queue<int> q;
int b, d[maxn], s[maxn], ex[maxn], ey[maxn];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &d[i], &s[i]);
    if (d[i] == 1)
      q.push(i);
  }
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    if (d[i] == 1) {
      ex[b] = i;
      ey[b] = s[i];
      b++;
      s[s[i]] ^= i;   // Update XOR sum of the neighbor
      d[s[i]]--;      // Decrease degree of neighbor
      if (d[s[i]] == 1)  // If neighbor now has degree 1, add it to queue
        q.push(s[i]);
    }
  }
  printf("%d\n", b);
  for (int i = 0; i < b; i++)
    printf("%d %d\n", ex[i], ey[i]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/