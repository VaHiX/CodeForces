// Problem: CF 689 B - Mike and Shortcuts
// https://codeforces.com/contest/689/problem/B

/*
Algorithm: Shortest Path using BFS with modified transitions
Approach:
- This problem can be modeled as a shortest path problem on a graph where:
  - Each node is an intersection.
  - There are three types of edges from each node `i`:
    1. A direct edge to `i-1` with weight `|i - (i-1)| = 1`
    2. A direct edge to `i+1` with weight `|i - (i+1)| = 1`
    3. A shortcut edge to `a[i]` with weight `1`
- We use BFS to process nodes in order of increasing distance.
- The BFS queue ensures that we compute the minimum distance to each node once.
- Each node can be updated by three possible transitions:
  - Moving left (i-1)
  - Moving right (i+1)
  - Using shortcut (a[i])

Time Complexity: O(n) - Each node is visited at most once.
Space Complexity: O(n) - For storing distances and the BFS queue.
*/

#include <cstdio>
#include <queue>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1);
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> dist(n + 1, -1);  // Initialize all distances to -1 (unvisited)
  dist[1] = 0;  // Starting point: distance to node 1 is 0
  std::queue<long> q;
  q.push(1);  // Start BFS from node 1
  while (!q.empty()) {
    long current = q.front();
    q.pop();
    long prev = current - 1;
    long next = current + 1;
    long path = a[current];
    long cand = 1 + dist[current];  // Candidate distance using current node's shortcut
    
    // Update previous node (current-1), only if it hasn't been visited or a better path exists
    if ((prev >= 1) && ((dist[prev] < 0) || (dist[prev] > cand))) {
      dist[prev] = cand;
      q.push(prev);
    }
    
    // Update next node (current+1)
    if ((next <= n) && ((dist[next] < 0) || (dist[next] > cand))) {
      dist[next] = cand;
      q.push(next);
    }
    
    // Update shortcut node a[current]
    if ((dist[path] < 0) || (dist[path] > cand)) {
      dist[path] = cand;
      q.push(path);
    }
  }
  
  for (long p = 1; p <= n; p++) {
    printf("%ld ", dist[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/