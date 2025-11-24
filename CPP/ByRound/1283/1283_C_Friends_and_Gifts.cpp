// Problem: CF 1283 C - Friends and Gifts
// https://codeforces.com/contest/1283/problem/C

/*
C. Friends and Gifts
Algorithm: Graph cycle detection and reassignment using priority queue
Approach:
- Build a directed graph from given mappings.
- Find all nodes that are not pointed to by any node (free positions).
- Assign these free positions to nodes with f[i] = 0.
- Handle cycles in the graph by swapping elements to resolve conflicts.

Time Complexity: O(n log n) due to priority queue operations
Space Complexity: O(n) for arrays and priority queue
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
priority_queue<int> q; // Stores unused numbers (positions not pointed to by anyone)
int n, a[200020], d[200020], b[200020]; // a: current assignment, d: visited/mark array, b: backup of original
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", a + i), b[i] = a[i], d[a[i]] = 1; // Read input and mark which numbers are used
  
  for (int i = 1; i <= n; i++)
    if (!d[i])
      q.push(i); // Add unused positions to priority queue (in descending order)
  
  for (int i = 1; i <= n; i++)
    if (!a[i])
      a[i] = q.top(), q.pop(); // Assign free positions to nodes with missing assignments
  
  for (int i = 1, j = 0; i <= n; i++)
    if (a[i] == i) { // If a node points to itself (cycle)
      while (b[j + 1] || j + 1 == i) // Find next valid position
        j = (j + 1) % n;
      swap(a[i], a[j + 1]); // Resolve self-loop by swapping with another node
    }
  
  for (int i = 1; i <= n; i++) {
    printf("%d ", a[i]);
  }
}


// https://github.com/VaHiX/codeForces/