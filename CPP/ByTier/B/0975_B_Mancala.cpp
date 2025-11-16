// Problem: CF 975 B - Mancala
// https://codeforces.com/contest/975/problem/B

/*
 * Code Purpose: This program computes the maximum score Resli can achieve in one move of the Mancala game.
 *               For each hole with stones, it simulates moving all stones counter-clockwise and calculates
 *               the score from collecting even-numbered holes.
 *
 * Algorithm: 
 *   - For each hole with a non-zero odd number of stones:
 *     - Simulate the move: redistribute all stones in counter-clockwise order.
 *     - Calculate score by summing up the stones in holes that end up with even numbers.
 *   - Track and return the maximum score among all possible moves.
 *
 * Time Complexity: O(N^2), where N = 14. Though N is fixed, the nested loop structure and per-move simulation
 *                  results in quadratic behavior with respect to the number of holes.
 *
 * Space Complexity: O(N), used to store the board state during each simulation.
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  const int N = 14;
  std::vector<ll> a(N, 0);
  for (ll p = 0; p < N; p++) {
    scanf("%lld", &a[p]);  // Read initial stone counts in each hole
  }
  ll mx(0);  // Initialize maximum score to 0
  for (ll p = 0; p < N; p++) {
    if (a[p] == 0) {
      continue;  // Skip holes with no stones
    }
    std::vector<ll> b = a;  // Copy current board state for simulation
    ll d = b[p];  // Number of stones to redistribute
    ll f = d / N;  // Base number of stones each hole gets
    d %= N;  // Extra stones to be distributed one by one
    b[p] = 0;  // Empty the starting hole
    ll w(0);  // Score accumulator for current move
    for (ll q = 1; q <= N; q++) {
      ll g = (p + q) % N;  // Calculate next hole index in counter-clockwise direction
      b[g] += (f + (d > 0));  // Distribute stones: base + one extra if needed
      --d;  // Decrease remaining extra stones
      if (b[g] % 2 == 0) {  // If the hole now has even number of stones
        w += b[g];  // Add to score
      }
    }
    mx = (mx > w) ? mx : w;  // Update maximum score
  }
  printf("%lld\n", mx);
  return 0;
}


// https://github.com/VaHiX/CodeForces/