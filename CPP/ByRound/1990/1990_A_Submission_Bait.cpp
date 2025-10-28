// Problem: CF 1990 A - Submission Bait
// https://codeforces.com/contest/1990/problem/A

/*
Problem: Determine if Alice has a winning strategy in a game played on an array.

Algorithms/Techniques:
- Game theory / greedy approach
- Sorting and checking pairs

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector

The game involves two players (Alice and Bob) taking turns. Each move consists of choosing an element >= current mx, setting mx to that value, and setting the element to 0.
Alice wins if she can make a move that forces Bob into a losing position.

Key insight:
- If n is odd, Alice always wins because she plays first and gets the last move.
- If n is even, it's more complex. The strategy involves checking if there are pairs of equal elements such that both players can take turns reducing them without leaving any valid moves for the opponent.
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    if (n % 2) {            // If n is odd, Alice always wins
      puts("YES");
      continue;
    }
    sort(v.rbegin(), v.rend());  // Sort in descending order to group same elements together
    
    bool res(false);
    for (long p = 1; !res && p < n; p += 2) {   // Check pairs of elements
      if (v[p - 1] == v[p]) {                   // If pair is equal, continue
        continue;
      }
      res = true;   // Found a mismatched pair, meaning Alice has winning strategy
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/