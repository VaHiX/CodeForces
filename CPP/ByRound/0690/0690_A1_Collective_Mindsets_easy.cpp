// Problem: CF 690 A1 - Collective Mindsets (easy)
// https://codeforces.com/contest/690/problem/A1

/*
 * Problem: Collective Mindsets (easy)
 * 
 * Purpose: Determine the minimum number of brains required for Heidi (the highest-ranked zombie) 
 *          to ensure her proposal is accepted by at least half of the attendees, allowing her 
 *          to take at least one brain home.
 *
 * Algorithm:
 * - This problem follows a classic game-theoretic approach known as the "Voting Game".
 * - Zombies are rational and prioritize survival above all else, followed by maximizing brains.
 * - Heidi (rank N) proposes first. To survive, she needs at least (N/2) + (N%2) votes, including her own.
 * - Key insight: Heidi can secure votes by offering brains to zombies who would otherwise get 0
 *   in the next round. She only needs enough brains to buy the votes of (N-1)/2 zombies.
 * - The minimum number of brains is (N+1)/2 because:
 *   - Heidi keeps at least 1 brain for herself.
 *   - She gives 1 brain to (N-1)/2 zombies (the ones who would get 0 otherwise) to secure their votes.
 *   - Total = 1 (for Heidi) + (N-1)/2 = (N+1)/2.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  printf("%ld\n", (n + 1) / 2);
  return 0;
}


// https://github.com/VaHiX/CodeForces/