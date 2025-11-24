// Problem: CF 469 A - I Wanna Be the Guy
// https://codeforces.com/contest/469/problem/A

/*
 * Code Purpose: Determine if two players, Little X and Little Y, can together complete all levels of a game.
 *               Each player can only complete a subset of levels. The goal is to check if their combined
 *               efforts cover all levels from 1 to n.
 *
 * Algorithms/Techniques: 
 *   - Use of std::set to store unique level indices that can be passed by either player.
 *   - Union of two sets to merge the levels passed by both players.
 *   - Size comparison of the merged set with total number of levels to determine if all levels are covered.
 *
 * Time Complexity: O(p + q + log(p + q)) where p and q are the number of levels each player can pass.
 *                  The log factor comes from insertion into a set.
 *
 * Space Complexity: O(p + q), for storing the set of passed levels.
 */

#include <cstdio>
#include <set>
int main() {
  int n;
  scanf("%d\n", &n);  // Read total number of levels
  std::set<int> pass;  // Set to store unique levels that can be passed
  int p;
  scanf("%d\n", &p);  // Read number of levels Little X can pass
  for (int k = 0; k < p; k++) {  // Loop through each level Little X can pass
    int temp;
    scanf("%d", &temp);
    pass.insert(temp);  // Insert level into the set
  }
  int q;
  scanf("%d\n", &q);  // Read number of levels Little Y can pass
  for (int k = 0; k < q; k++) {  // Loop through each level Little Y can pass
    int temp;
    scanf("%d", &temp);
    pass.insert(temp);  // Insert level into the set
  }
  // Check if all levels (1 to n) are covered by the union of both players' levels
  puts(pass.size() >= n ? "I become the guy." : "Oh, my keyboard!");
  return 0;
}


// https://github.com/VaHiX/CodeForces/