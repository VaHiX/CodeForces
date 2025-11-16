// Problem: CF 1681 B - Card Trick
// https://codeforces.com/contest/1681/problem/B

/*
B. Card Trick
Algorithms/Techniques: Simulation with modular arithmetic to track top card position.
Time Complexity: O(n + m) per testcase, where n is number of cards and m is number of shuffles.
Space Complexity: O(n) for storing the card values.

The problem simulates a deck of cards being shuffled by moving topmost cards to the bottom,
and we need to determine the value of the topmost card after all shuffles.
Instead of actually simulating the array, we track the index of the top card
using modular arithmetic. Each shuffle operation modifies this index,
and we compute the final index modulo n to get the result.

Input:
- Number of test cases t
- For each test case:
  - n: number of cards
  - Array a of n distinct integers representing card values
  - m: number of shuffles
  - Array b of m integers representing number of top cards moved in each shuffle

Output:
- The value of the topmost card after all shuffles
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
    long m;
    scanf("%ld", &m);
    long idx(0); // Start with the topmost card index
    while (m--) {
      long x;
      scanf("%ld", &x);
      idx += x;  // Move to the new top card position after moving x cards
      idx %= n;  // Use modular arithmetic to wrap around
    }
    printf("%ld\n", a[idx]);
  }
}


// https://github.com/VaHiX/codeForces/