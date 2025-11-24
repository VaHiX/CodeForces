// Problem: CF 1526 C1 - Potions (Easy Version)
// https://codeforces.com/contest/1526/problem/C1

/*
Algorithm: Greedy with Priority Queue
Approach:
- Process potions from left to right.
- Keep a running sum of health (cur).
- Use a min-heap (priority queue) to store the health changes of potions we've taken.
- If adding a potion causes health to drop below zero, we must discard the potion with the smallest health change (from the min-heap) to maintain non-negative health.
- The size of the priority queue at the end is the maximum number of potions that can be drunk.

Time Complexity: O(n log n) - Each element is pushed and popped from the priority queue at most once, and each operation takes O(log n) time.
Space Complexity: O(n) - The priority queue stores at most n elements.
*/

#include <cstdio>
#include <queue>
#include <vector>
#include <functional>

int main() {
  long n;
  scanf("%ld", &n);
  std::priority_queue<long, std::vector<long>, std::greater<long>> pq; // Min-heap to store potions we've taken
  long long cur(0); // Current health
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    cur += x; // Add potion effect to health
    pq.push(x); // Add the potion to our collection
    // If health becomes negative, remove the potion with the smallest effect (the one that contributed least to health)
    while ((cur < 0) && (!pq.empty())) {
      cur -= pq.top(); // Remove the smallest potion effect (worst contributing potion)
      pq.pop(); // Remove it from our collection
    }
  }
  printf("%ld\n", pq.size()); // Output number of potions we could drink
}


// https://github.com/VaHiX/CodeForces/