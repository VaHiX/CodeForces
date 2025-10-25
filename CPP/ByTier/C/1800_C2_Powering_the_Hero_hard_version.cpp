// Problem: CF 1800 C2 - Powering the Hero (hard version)
// https://codeforces.com/contest/1800/problem/C2

/*
C2. Powering the Hero (hard version)
Algorithm: Greedy with Max Heap (priority_queue)
Time Complexity: O(n log n) per test case, where n is the number of cards
Space Complexity: O(n) for the priority queue storage

The problem involves maximizing the total power of an army formed by using hero cards
and bonus cards. Hero cards (with power 0) can be "powered up" by using the highest 
available bonus card from a deck. A max heap is used to efficiently retrieve the 
maximum available bonus card at each step when a hero card is encountered.
*/

#include <cstdio>
#include <queue>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::priority_queue<long> ds; // Max heap to store bonus cards
    long long res(0); // Result accumulator for total army power
    for (long p = 0; p < n; p++) {
      long long x;
      scanf("%lld", &x);
      if (x) { // If it's a bonus card (non-zero)
        ds.push(x); // Add to the max heap
      } else if (!ds.empty()) { // If it's a hero card and we have bonuses
        res += ds.top(); // Use the highest bonus power
        ds.pop(); // Remove used bonus
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/