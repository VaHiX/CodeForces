// Problem: CF 490 B - Queue
// https://codeforces.com/contest/490/problem/B

/*
 * Problem: Restore a queue of students based on their neighbors' IDs.
 * 
 * Approach:
 * - Use a map to store the relationship between each student and their next neighbor.
 * - Identify the starting point (student with no previous student) and ending point (student with no next student).
 * - Build the queue by traversing from start to end and filling even/odd indices accordingly.
 * 
 * Time Complexity: O(n log n)
 *   - Insertion and lookup in map takes O(log n) per operation.
 *   - Traversals through the map and set are linear in the number of elements.
 * 
 * Space Complexity: O(n)
 *   - Storing all student relationships in the map and sequence vector.
 */

#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> sequence(n, 0); // Vector to store the final sequence
  std::map<long, long> order; // Map to store the next student for each student (before -> after)
  
  for (long p = 0; p < n; p++) {
    long before, after;
    scanf("%ld %ld\n", &before, &after);
    order.insert(std::pair<long, long>(before, after));
  }
  
  long current = 0; // Start from student 0 (initially)
  // Traverse and fill even positions (starting from index 1)
  for (long p = 1; p < n; p += 2) {
    if (order.find(current) == order.end()) {
      break; // No more connections
    }
    sequence[p] = order[current]; // Set the next student
    order.erase(current); // Remove current to avoid reprocessing
    current = sequence[p]; // Move to the next student
  }
  
  std::set<long> remainingNodes; // Set to track nodes that have no incoming or outgoing edges
  // Identify the last student (the one with no follower)
  for (std::map<long, long>::iterator mapIter = order.begin();
       mapIter != order.end(); mapIter++) {
    if (mapIter->second == 0) {
      sequence[n - 2] = mapIter->first; // Set the last element in the sequence
      continue;
    }
    remainingNodes.insert(mapIter->first); // Add nodes to the set
    remainingNodes.insert(mapIter->second); // Add their neighbors too
  }
  
  // Remove the neighbors from the set to find the starting student
  for (std::map<long, long>::iterator mapIter = order.begin();
       mapIter != order.end(); mapIter++) {
    remainingNodes.erase(mapIter->second); // Remove followers, leaving only starters or enders
  }
  
  current = (remainingNodes.size() > 0) ? (*remainingNodes.begin()) : -1; // Get the first student
  
  // Fill odd positions (starting from index 0) with the forward traversal
  for (long p = 0; p < n; p += 2) {
    if (current < 0) {
      break; // Stop if no more students to process
    }
    sequence[p] = current; // Set current student
    if (order.find(current) == order.end() || order[current] == 0) {
      break; // Stop if no next student
    }
    current = order[current]; // Move to the next student
  }
  
  // Print the final sequence
  for (long p = 0; p < n; p++) {
    printf("%ld ", sequence[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/