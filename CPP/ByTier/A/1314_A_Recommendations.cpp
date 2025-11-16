// Problem: CF 1314 A - Recommendations
// https://codeforces.com/contest/1314/problem/A

/*
 * Problem: VK news recommendation system optimization
 * Purpose: Minimize total time to make all news categories have distinct publication counts.
 * Algorithm:
 *   - Sort categories by their base count (a_i)
 *   - Use greedy approach with priority queue:
 *     * For each category, if we can reduce the count of previous categories,
 *       pop from PQ and accumulate time cost
 *     * Add current category's time to total and push its time to PQ
 *   - After processing, clean up remaining elements in PQ
 * Time Complexity: O(n log n) due to sorting and priority queue operations
 * Space Complexity: O(n) for storing categories and priority queue
 */

#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;
priority_queue<int> PQ; // Priority queue to keep track of time costs for adding publications
long long s; // Running sum of times in priority queue
long long res; // Total minimum time required
int n; // Number of categories
struct point {
  int a, b; // a: base count, b: time to add one publication
  bool operator<(const point &p) const { return a < p.a; } // Sort by base count
} w[201000]; // Array to store categories

int main() {
  int i;
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d", &w[i].a); // Read base counts
  for (i = 1; i <= n; i++)
    scanf("%d", &w[i].b); // Read time costs
  sort(w + 1, w + n + 1); // Sort by base count

  int cur = 0; // Current number of publications processed so far
  for (i = 1; i <= n; i++) {
    // While we can still add more items to smaller categories and PQ is not empty
    while (cur < w[i].a && !PQ.empty()) {
      s -= PQ.top(); // Remove largest time cost from running sum
      res += s; // Add this sum to total result
      PQ.pop(); // Pop the element
      cur++; // Increment current count
    }
    cur = w[i].a; // Set current count to a_i of this category
    s += w[i].b; // Add time cost for this category to running sum
    PQ.push(w[i].b); // Push the time cost to priority queue
  }

  // Process remaining elements in the priority queue
  while (!PQ.empty()) {
    s -= PQ.top(); // Remove largest time cost from running sum
    res += s; // Add this sum to total result
    PQ.pop(); // Pop the element
  }
  
  printf("%lld\n", res); // Output the minimum required time
}


// https://github.com/VaHiX/codeForces/