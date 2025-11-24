// Problem: CF 1800 C1 - Powering the Hero (easy version)
// https://codeforces.com/contest/1800/problem/C1

/*
C1. Powering the Hero (easy version)
Algorithm: Greedy with Max Heap (priority_queue)
Time Complexity: O(n log n) per test case, where n is the number of cards.
Space Complexity: O(n) for the priority queue in worst case.

The problem simulates a deck of cards where:
- Hero cards have power 0 and can activate the top bonus card.
- Bonus cards have positive power and can be used to boost hero cards.
We use a max heap (priority_queue) to always pick the highest available bonus card
to power up heroes, maximizing the total army power.

Key idea:
1. Process cards from top to bottom.
2. For each bonus card (non-zero), push it into max heap.
3. For each hero card (zero), use the largest bonus card from heap if available.
4. Accumulate the sum of used bonus powers as result.
*/

#include <cstdio>
#include <queue>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) { // Process each test case
    long n;
    scanf("%ld", &n);
    std::priority_queue<long> ds; // Max heap to store bonus card powers
    long long res(0); // Result sum of used bonus powers
    for (long p = 0; p < n; p++) {
      long long x;
      scanf("%lld", &x);
      if (x) { // If card is a bonus card (non-zero)
        ds.push(x); // Add to heap
      } else if (!ds.empty()) { // If card is a hero card and we have bonuses
        res += ds.top(); // Use the highest bonus
        ds.pop(); // Remove used bonus
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/