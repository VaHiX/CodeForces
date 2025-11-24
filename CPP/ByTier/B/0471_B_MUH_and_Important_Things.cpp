// Problem: CF 471 B - MUH and Important Things
// https://codeforces.com/contest/471/problem/B

/*
 * Problem: MUH and Important Things
 * 
 * Purpose: 
 *   Given a list of tasks with difficulty levels, we need to find three distinct orders
 *   in which these tasks can be performed such that each order respects the difficulty
 *   constraints (tasks with same difficulty can be done in any order). If possible,
 *   output any three such orders; otherwise, print "NO".
 * 
 * Approach:
 *   1. Read task difficulties and store them with their original indices.
 *   2. Sort tasks by difficulty.
 *   3. Identify if there exists at least one difficulty level with at least 2 tasks.
 *      - If not, no valid permutations exist (return "NO").
 *   4. Generate three distinct permutations by swapping pairs of tasks with the same difficulty.
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing tasks and their indices
 * 
 * Algorithms/Techniques:
 *   - Sorting
 *   - Greedy approach to identify conflict points
 *   - Swapping elements to create distinct sequences
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  int n;
  scanf("%d\n", &n);
  std::vector<std::pair<int, int>> tasks(n);
  for (int p = 0; p < n; p++) {
    int temp;
    scanf("%d", &temp);
    tasks[p] = std::pair<int, int>(temp, 1 + p); // Store difficulty and original index (1-based)
  }
  std::sort(tasks.begin(), tasks.end()); // Sort by difficulty level

  int a = -1, b = -1;
  // Find first and second occurrence of duplicate difficulty levels
  for (int p = 0; p < tasks.size() - 1; p++) {
    if (tasks[p].first == tasks[p + 1].first) {
      if (a < 0) {
        a = p; // First index of duplicate difficulty
      } else {
        b = p; // Second index of duplicate difficulty
        break;
      }
    }
  }
  
  if (b < 0) {
    puts("NO"); // No two tasks share the same difficulty level
  } else {
    puts("YES");
    // Print first permutation (original sorted order)
    for (int p = 0; p < tasks.size(); p++) {
      printf("%d ", tasks[p].second);
    };
    puts("");
    
    // Swap elements at positions a and a+1 to generate second permutation
    int temp;
    temp = tasks[a].second;
    tasks[a].second = tasks[a + 1].second;
    tasks[a + 1].second = temp;
    for (int p = 0; p < tasks.size(); p++) {
      printf("%d ", tasks[p].second);
    }
    puts("");
    
    // Swap elements at positions b and b+1 to generate third permutation
    temp = tasks[b].second;
    tasks[b].second = tasks[b + 1].second;
    tasks[b + 1].second = temp;
    for (int p = 0; p < tasks.size(); p++) {
      printf("%d ", tasks[p].second);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/