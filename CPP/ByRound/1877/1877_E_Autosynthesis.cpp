// Problem: CF 1877 E - Autosynthesis
// https://codeforces.com/contest/1877/problem/E

/*
 * Problem: E. Autosynthesis
 * 
 * Purpose: Given an array of positive integers, determine a sequence of operations
 *          such that the uncircled elements (in order) equal the sequence of 
 *          indices of circled elements.
 * 
 * Algorithm:
 * 1. Build a graph where each element points to the index of the value it holds.
 * 2. Use topological sorting to detect nodes with zero in-degree and mark them.
 * 3. Identify cycles in the graph to determine if a valid solution exists.
 * 4. For each cycle, check if the cycle length is even.
 * 5. Output the indices of elements that were circled during the process.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Topological sort with queue
 * - Cycle detection in directed graph
 * - Greedy selection for valid operations
 */

#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;
#define N 200010
int n, a[N], deg[N], ans[N], f[N];
int p, u, cnt;
queue<int> q;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    deg[a[i]]++; // Count incoming edges to detect nodes with no incoming edges
  }
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) { // Nodes with no incoming edges are those that cannot be reached
      ans[i] = 1; // Mark them as circled
      q.push(i);  // Add to queue for processing
    }
  }
  while (!q.empty()) {
    p = q.front(); // Process node from queue
    q.pop();
    f[p] = ans[p] = 1; // Mark node as processed and circled
    if (!f[a[p]] && --deg[a[a[p]]] == 0) { // Update adjacent node's in-degree and push if zero
      q.push(a[a[p]]);
    }
    f[a[p]] = 1; // Mark adjacent node as processed
  }
  for (int i = 1; i <= n; i++) {
    if (!f[i]) { // If not processed yet, part of a cycle
      u = a[i]; // Start traversing the cycle
      cnt = 1;  // Count cycle length
      f[i] = 1; // Mark current node as processed
      while (u != i) { // Traverse until back to start
        if (cnt & 1) { // If odd step, mark it for circling (for balancing)
          ans[u] = 1;
        }
        f[u] = 1; // Mark current node as processed
        u = a[u]; // Move to next node in cycle
        cnt++;    // Increment step count
      }
      if (cnt & 1) { // If cycle length is odd, impossible to satisfy condition
        printf("-1\n");
        return 0;
      }
    }
  }
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (ans[i]) {
      cnt++; // Count number of operations
    }
  }
  printf("%d\n", cnt); // Output number of operations
  for (int i = 1; i <= n; i++) {
    if (ans[i]) {
      printf("%d ", a[i]); // Print index of circled element
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/