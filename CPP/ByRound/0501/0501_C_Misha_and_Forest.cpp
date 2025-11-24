// Problem: CF 501 C - Misha and Forest
// https://codeforces.com/contest/501/problem/C

/*
 * Problem: Misha and Forest
 * Algorithm: BFS-based forest reconstruction using degree and XOR sum properties
 * 
 * Key Idea:
 * - Each vertex has a degree and an XOR sum of its neighbors.
 * - In a forest, we can process leaves (degree 1) first.
 * - For a leaf v with degree 1 and XOR sum s[v], the only neighbor is s[v].
 * - After connecting v to s[v], we update the neighbor's degree and XOR sum.
 * - Continue processing until all edges are determined.
 * 
 * Time Complexity: O(n)
 *   - Each vertex is processed at most once, and each edge is considered once.
 * Space Complexity: O(n)
 *   - Storage for degree, s arrays, queue, and edges.
 * 
 * Technique: 
 * - BFS-like processing using deque for leaf nodes.
 * - XOR properties to maintain neighbor sums.
 */

#include <deque>
#include <iostream>
#include <vector>
#include <utility>

int main() {
  long n;
  std::cin >> n;
  std::vector<long> degree(n, 0);  // Stores degree of each vertex
  std::vector<long> s(n, 0);       // Stores XOR sum of neighbors for each vertex
  std::deque<long> queue;          // Queue to hold leaves (degree 1) for processing
  
  for (long p = 0; p < n; p++) {
    std::cin >> degree[p] >> s[p];
    if (degree[p] == 1) {
      queue.push_front(p);  // Add leaf to front of queue for processing
    }
  }
  
  std::vector<std::pair<long, long>> edges;  // To store the resulting edges
  
  while (!queue.empty()) {
    long leaf = queue.back();  // Get a leaf from the back
    queue.pop_back();          // Remove it from the queue
    
    if (degree[leaf] < 1) {
      continue;  // Skip if already processed
    }
    
    long parent = s[leaf];  // The neighbor of leaf is the XOR sum
    edges.push_back(std::pair<long, long>(leaf, parent));  // Add edge to result
    --degree[parent];  // Reduce degree of parent since it's connected now
    
    if (degree[parent] == 1) {
      queue.push_front(parent);  // If parent becomes a leaf, add to queue
    }
    
    s[parent] ^= leaf;  // Update XOR sum of the parent (remove the leaf)
  }
  
  std::cout << edges.size() << std::endl;  // Output number of edges
  for (long p = 0; p < edges.size(); p++) {
    std::cout << edges[p].first << " " << edges[p].second << std::endl;  // Output each edge
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/