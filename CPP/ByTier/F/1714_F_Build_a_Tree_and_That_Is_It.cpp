// Problem: CF 1714 F - Build a Tree and That Is It
// https://codeforces.com/contest/1714/problem/F

/*
 * Problem: Build a Tree and That Is It
 * 
 * Purpose: 
 *   Given four integers n, d12, d23, d31, construct a tree with n vertices such that:
 *   - Distance from vertex 1 to 2 is d12
 *   - Distance from vertex 2 to 3 is d23
 *   - Distance from vertex 3 to 1 is d31
 * 
 * Algorithm:
 *   1. Use the triangle inequality to verify if a valid tree can be constructed.
 *   2. Calculate the number of internal nodes required to satisfy the distances.
 *   3. Build the tree by connecting the three vertices with the required distances.
 *   4. Attach remaining nodes to vertex 1.
 * 
 * Time Complexity: O(1) per test case (as the number of operations is constant, regardless of n).
 * Space Complexity: O(1) for each test case (no extra space used except for a few variables).
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back
using namespace std;
int T, n, now, d[5], a[5];

// Function to print a path from u to v with specified distance
void print(int u, int v, int dis) {
  if (u == v)
    return;
  vector<int> V;
  V.pb(u);
  --dis;
  while (dis--)
    V.pb(++now);  // Increment now and add to path
  V.pb(v);
  for (int i = 0; i < V.size() - 1; i++)
    printf("%d %d\n", V[i], V[i + 1]);
  return;
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &d[1], &d[2], &d[3]);
    int s = d[1] + d[2] + d[3];
    if (s & 1) {
      puts("NO");
      continue;
    }
    s >>= 1;
    // Calculate the distances from each vertex to the center (or a common node)
    a[1] = s - d[2], a[2] = s - d[3], a[3] = s - d[1];
    if (a[1] < 0 || a[2] < 0 || a[3] < 0 || a[1] + a[2] + a[3] + 1 > n) {
      puts("NO");
      continue;
    }
    puts("YES");
    now = 3;
    int rt = 0;
    // Find a vertex that is not connected to any other vertex (a[1] = 0)
    for (int i = 1; i <= 3; i++)
      if (!a[i]) {
        rt = i;
        break;
      }
    if (!rt)
      rt = ++now;  // If no such vertex, set new root
    for (int i = 1; i <= 3; i++)
      print(rt, i, a[i]);  // Print the path from root to each vertex
    for (++now; now <= n; now++)
      printf("1 %d\n", now);  // Attach all remaining nodes to vertex 1
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/