// Problem: CF 1740 D - Knowledge Cards
// https://codeforces.com/contest/1740/problem/D

/*
 * Problem: D. Knowledge Cards
 *
 * Purpose: Determine if a puzzle involving moving cards from (1,1) to (n,m)
 *          on an n x m grid can be solved such that the final stack at (n,m)
 *          has cards numbered 1 to k in that order from top to bottom.
 *
 * Algorithm:
 * - For each card with number 'x' in the initial stack, we must move it to
 *   the final position (n,m). The minimum number of steps required to move
 *   a card from (1,1) to (n,m) is (n-1) + (m-1) = n + m - 2.
 * - However, we also need to account for how many cards are already placed
 *   in intermediate positions before placing card 'x'. Specifically, if card
 *   'x' is at position 'i' in the initial stack, it needs to pass through
 *   at least 'i-1' intermediate cells (since we must move other cards before
 * it).
 * - So, if at any point the number of available moves (i.e., n*m + k) is
 * insufficient to place the card 'x', it's impossible. The condition used is:
 *   n*m + k <= 2 + x + i (where x is the value on card, i is its index in the
 * stack).
 *
 * Time Complexity: O(k) per test case, since we iterate through the k cards
 * once. Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <bits/stdc++.h>
using namespace std;

char s[2][114515] = {"YA", "TIDAK"};
int main() {
  int T;
  cin >> T;
  while (T--) {
    int f = 1, n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
      int x;
      cin >> x;
      // Check if number of available cells and moves is sufficient
      // for placing the current card at position i with value x
      if (n * m + k <= 2 + x + i)
        f = 0;
    }
    puts(s[!f]);
  }
}

// https://github.com/VaHiX/CodeForces/