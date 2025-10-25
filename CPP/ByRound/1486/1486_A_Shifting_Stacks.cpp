// Problem: CF 1486 A - Shifting Stacks
// https://codeforces.com/contest/1486/problem/A

/*
 * Problem: A. Shifting Stacks
 * Task: Determine if we can make the sequence of stack heights strictly increasing
 *       by moving blocks from a stack to the next one (to the right).
 *
 * Algorithm:
 *   - Process stacks from left to right.
 *   - Keep track of "carry" which represents how many blocks have been moved
 *     from previous stacks and are now available to be placed in the current stack.
 *   - For each stack, add the carry to its height (since we can use blocks from
 *     previous stacks that were shifted).
 *   - Check if the resulting height is at least equal to the current position index
 *     (0-based) to ensure it's strictly increasing.
 *   - Update carry to be the number of blocks left after placing the required minimum
 *     to maintain a strictly increasing sequence.
 *
 * Time Complexity: O(n) per test case, where n is the number of stacks.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll carry(0);               // Tracks how many blocks are "carried" forward from previous stacks
    bool res(true);            // Flag to store result, initially true
    for (ll p = 0; p < n; p++) {   // Iterate through each stack
      ll h;
      scanf("%lld", &h);
      h += carry;              // Add carried blocks to current stack's height
      if (h < p) {             // If after adding carry, current height is less than required for strictly increasing order
        res = false;           // Mark as impossible
      }
      carry = h - p;           // Update carry: how many blocks remain after satisfying minimum needed for position p
    }
    puts(res ? "YES" : "NO");  // Output result
  }
}


// https://github.com/VaHiX/codeForces/