// Problem: CF 1161 A - Hide and Seek
// https://codeforces.com/contest/1161/problem/A

/*
 * Problem: Hide and Seek
 * Algorithms/Techniques: Simulation, Interval analysis
 *
 * Time Complexity: O(n + k)
 * Space Complexity: O(n)
 *
 * Description:
 * Alice and Bob play a game on a line with n cells. Bob asks k questions about
 * where Alice's token might be. Alice is allowed to move her token at most once
 * (to an adjacent cell) between any two questions, or before/after all questions.
 * Alice answers NO to each question, meaning she does not stay on the queried cell.
 * The task is to count how many valid (start, end) pairs of positions can exist such that
 * Alice can avoid every queried cell regardless of where she moves.
 *
 * Approach:
 * - For each cell that was queried (w[i]), track first and last occurrence.
 * - For each possible starting position i:
 *   - Check if Alice could start there without being caught.
 *   - Check if she can avoid the queries by moving to adjacent cells.
 * - The valid scenarios are those where the move doesn't put her in a query cell,
 *   or she can escape from any previous query.
 */

#include <cstdio>
#include <iosfwd>

using namespace std;
int n, K, L[101000], R[101000], w[101000], res;

int main() {
  int i;
  scanf("%d%d", &n, &K);
  // Initialize left and right arrays to extreme values
  for (i = 1; i <= n; i++)
    L[i] = 1e9, R[i] = -1;
  
  // Process Bob's guesses: store first and last occurrence of each guessed cell
  for (i = 1; i <= K; i++) {
    scanf("%d", &w[i]);
    R[w[i]] = i;                // Rightmost query index for this cell
    if (L[w[i]] > K)           // If never seen before, store first index
      L[w[i]] = i;
  }
  
  // Iterate over all possible starting positions and count valid end positions
  for (i = 1; i <= n; i++) {
    // If cell i was never queried, Alice can start here (res++)
    if (L[i] > K)
      res++;
    
    // If Alice can move from cell i to previous cell (and avoid the query there)
    if (i > 1 && L[i] > R[i - 1])
      res++;
    
    // If Alice can move from cell i to next cell (and avoid the query there)
    if (i < n && L[i] > R[i + 1])
      res++;
  }
  
  printf("%d\n", res);
}


// https://github.com/VaHiX/codeForces/