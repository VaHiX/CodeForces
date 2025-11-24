// Problem: CF 1965 A - Everything Nim
// https://codeforces.com/contest/1965/problem/A

/*
 * Problem: Everything Nim
 * Algorithms/Techniques: Game Theory, Sprague-Grundy Theorem, Nim-sum
 * 
 * Time Complexity: O(n log n) per test case due to sorting and unique operations.
 * Space Complexity: O(n) for storing the pile sizes.
 *
 * Description:
 * This is a variant of the Nim game where players can remove equal amounts of stones
 * from all non-empty piles in each move. The key insight is that the game is equivalent
 * to the standard Nim game, and thus can be solved using XOR (nim-sum) of all pile sizes.
 * 
 * The algorithm:
 * 1. Sort and deduplicate the pile sizes.
 * 2. Compute the nim-sum (XOR) of all pile sizes.
 * 3. If the nim-sum is zero, the current player (Alice) loses; otherwise, Alice wins.
 * 
 * However, this implementation seems to use a different approach,
 * possibly based on counting how many piles equal their 1-indexed position after sorting.
 * This logic computes an index `x` such that `a[x] == x`, then determines the winner
 * depending on whether `x` equals `n` and its parity.
 */

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 200010;
int T, n, x, a[N];

void solve() {
  cin >> n;  // Read number of piles
  for (int i = 1; i <= n; ++i)
    cin >> a[i];  // Read pile sizes
  
  sort(a + 1, a + n + 1);  // Sort the array
  n = unique(a + 1, a + n + 1) - a - 1;  // Remove duplicates and update n
  x = 0;  // Initialize variable to store some key index
  
  for (int i = 1; i <= n; ++i)
    if (a[i] == i)  // Find the position where value equals index
      x = i;
  
  // Game result determination:
  // If x == n and x is even -> Bob wins
  // Else -> Alice wins (based on parity logic)
  cout << (((x == n) != (x & 1)) ? "Bob" : "Alice") << endl;
}

int main() {
  for (ios::sync_with_stdio(0), cin >> T; T--;)  // Fast input
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/