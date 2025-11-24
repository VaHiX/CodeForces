// Problem: CF 1352 D - Alice, Bob and Candies
// https://codeforces.com/contest/1352/problem/D

/*
D. Alice, Bob and Candies
Algorithm: Two-pointer simulation with greedy strategy.
Time Complexity: O(n) per test case, where n is the number of candies.
Space Complexity: O(n) due to the vector storing candy sizes.

The game proceeds with Alice and Bob alternating moves:
- Alice starts first and eats from left to right.
- Bob eats from right to left.
- Each player must eat a total size strictly greater than the previous opponent's move.
- The game ends when no more candies are available to satisfy the condition.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long cnt(0), alice(0), bob(0); // cnt: number of moves, alice/bob: total eaten
    long x(0), y(n - 1);           // x: left pointer, y: right pointer
    long cur(0), prev(0);          // cur: current move sum, prev: previous move sum
    while (x <= y) {
      // Alice's turn: eat from left until current sum > previous
      while ((x <= y) && (cur <= prev)) {
        cur += a[x];       // add candy to current move
        alice += a[x];     // update Alice's total
        ++x;               // move pointer
      }
      prev = cur;          // update previous sum to current
      cnt += (cur > 0);    // increment move count if valid move
      cur = 0;             // reset for next player's turn

      // Bob's turn: eat from right until current sum > previous
      while ((x <= y) && (cur <= prev)) {
        cur += a[y];       // add candy to current move
        bob += a[y];       // update Bob's total
        --y;               // move pointer
      }
      prev = cur;          // update previous sum to current
      cnt += (cur > 0);    // increment move count if valid move
      cur = 0;             // reset for next player's turn
    }
    printf("%ld %ld %ld\n", cnt, alice, bob);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/