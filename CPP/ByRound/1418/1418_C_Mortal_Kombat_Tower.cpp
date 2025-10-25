// Problem: CF 1418 C - Mortal Kombat Tower
// https://codeforces.com/contest/1418/problem/C

/*
C. Mortal Kombat Tower
Algorithm: Greedy approach to minimize skip points.
Time Complexity: O(n) where n is the number of bosses per test case.
Space Complexity: O(1) - only using a few variables for tracking.

The problem involves two players (you and your friend) taking turns killing bosses,
with the constraint that each player can kill 1 or 2 bosses per turn. Your friend
cannot kill hard bosses (a_i = 1), so must use skip points for them.

We process the sequence of bosses greedily:
- When we encounter three consecutive hard bosses, we can optimize by letting one 
  player kill two of these and the other player kill the third.
- This strategy minimizes the number of skips needed.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt; // Count of skip points needed
    scanf("%ld", &cnt);
    int prev(0), pprev(0); // Track previous and previous-previous boss types
    
    for (long p = 1; p < n; p++) { // Start from second boss since we compare with predecessors
      int x;
      scanf("%d", &x);
      
      // If there are three consecutive hard bosses (pprev=1, prev=1, x=1),
      // it's optimal to let one player kill the middle one and the other two,
      // so increment skip count and set current boss as killed (x=0)
      if (pprev && prev && x) {
        ++cnt;
        x = 0;
      }
      
      pprev = prev; // Shift window
      prev = x;     // Shift window
    }
    
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/