// Problem: CF 1774 F2 - Magician and Pigs (Hard Version)
// https://codeforces.com/contest/1774/problem/F2

/*
 * Problem: F2. Magician and Pigs (Hard Version)
 * 
 * Purpose:
 *   This code simulates a sequence of operations on pigs' health points and determines the final number of surviving pigs.
 *   The operations include creating pigs, reducing health of all pigs, and repeating all previous operations.
 *   The key idea is to process operations efficiently using a technique that tracks how many times each operation (especially repetition) affects the current state.
 * 
 * Algorithm:
 *   - We simulate the operations but use a compressed representation for repeated operations.
 *   - A state stack is used to represent multiple operations at once:
 *     - Each level of the stack stores:
 *       - sub: cumulative reduction applied to all pigs up to this point
 *       - basis: starting health threshold before this level
 *       - add: list of base health values for pigs created at this level
 *   - Repeating operations cause a new level to be pushed onto the stack.
 *   - The final computation counts surviving pigs using dynamic programming over the operation stack.
 * 
 * Time Complexity: O(n log n)
 *   - Each operation is processed in O(1) time.
 *   - The solve() function processes the accumulated state.
 *   - For repeated operations, the stack depth is bounded by log(n) due to binary representation.
 * 
 * Space Complexity: O(n)
 *   - Stack storage for operation states.
 *   - Additional arrays for tracking counts and intermediate results.
 */
#include <stdio.h>
#include <vector>
#define int long long
using namespace std;
int n, top = 0, ign = 0, w[1000005], counter;
struct {
  int sub, basis;
  vector<int> add;
} state[40];
// Function to compute how many times a health value survives across repeated operations
int count_repr(int val, int i) {
  int ans = 1, j = top;
  while (j >= i) {
    if (val >= state[j].basis) {
      ans += 1 << (j - i);
      val -= state[j].basis;
    }
    j--;
  }
  return ans;
}
// Compute final answer by processing all pig states
void solve() {
  int total = 0, counter = 0;
  for (int i = 0; i <= top; i++)
    for (int val : state[i].add) {
      for (int j = i; j <= top; j++)
        val -= state[j].sub;
      if (val > 0)
        total = (total + w[counter + 1] * count_repr(val - 1, i)) % 998244353;
      counter++;
    }
  printf("%lld", total);
}
signed main() {
  scanf("%lld", &n);
  int current = 0, counter = 0;
  // Initialize the state structure
  for (int i = 0; i < 40; i++)
    state[i] = {0, (int)1e10, {}};
  for (int i = 0; i < n; i++) {
    int op, x;
    scanf("%lld", &op);
    if (op == 1) {
      // Create pig with x health
      scanf("%lld", &x);
      state[top].add.push_back(x + state[top].sub);
      counter++;
    } else if (op == 2) {
      // Reduce all pig health by x
      scanf("%lld", &x);
      state[top].sub += x;
    } else {
      // Repeat all operations until now
      if (ign)
        continue;
      if (top == 0 && state[top].sub == 0) {
        // Special case for repeated operations
        w[counter] = w[counter] == 0 ? 2 : w[counter] * 2 % 998244353;
        continue;
      }
      // Update basis for next level
      state[top].basis =
          state[top].sub + 2 * (top == 0 ? 0 : state[top - 1].basis);
      if (state[top].basis > 2e9) {
        // If basis exceeds limit, ignore further repetitions
        ign = 1;
        continue;
      }
      top++;
    }
  }
  // Precompute powers of 2 for fast counting
  for (int i = counter, v = 1; i >= 0; i--)
    w[i] = w[i] == 0 ? v : v = (w[i] * v) % 998244353;
  solve();
}


// https://github.com/VaHiX/CodeForces/