// Problem: CF 1526 C2 - Potions (Hard Version)
// https://codeforces.com/contest/1526/problem/C2

/*
Algorithm: Greedy with Min-Heap
Approach:
- Iterate through potions from left to right.
- Keep a running sum of health (cur).
- Use a min-heap (priority queue) to store the potions we have drunk so far.
- If adding a new potion makes our health negative, we greedily remove the potion with the smallest gain (from the heap) to try to recover.
- Continue this process until we've processed all potions.
- The size of the heap at the end is the maximum number of potions we can drink.

Time Complexity: O(n log n) - Each element is pushed and popped from the heap at most once, and each heap operation takes O(log n).
Space Complexity: O(n) - For storing the heap.

The solution works by maintaining a valid prefix of potions that keeps the health non-negative,
and greedily optimizes by removing the smallest positive potions (in terms of health gain) when needed.
*/

#include <cstdio>
#include <queue>
#include <vector>
#include <functional>

int main() {
  long n;
  scanf("%ld", &n);
  std::priority_queue<long, std::vector<long>, std::greater<long>> pq; // Min-heap to store potions we've drunk
  long long cur(0); // Current health
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    cur += x; // Add potion to current health
    pq.push(x); // Add potion to the heap
    while ((cur < 0) && (!pq.empty())) {
      // If health becomes negative, remove the potion with the smallest gain
      cur -= pq.top();
      pq.pop();
    }
  }
  printf("%ld\n", pq.size()); // Number of potions we can drink
}


// https://github.com/VaHiX/CodeForces/