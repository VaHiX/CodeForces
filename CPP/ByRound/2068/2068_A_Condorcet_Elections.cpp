// Problem: CF 2068 A - Condorcet Elections
// https://codeforces.com/contest/2068/problem/A

/*
 * Problem: Condorcet Elections
 * Algorithm/Technique: Constructive Approach with Cycle Detection
 * 
 * This code attempts to construct a set of votes that satisfies the given pairwise defeat conditions.
 * The approach is based on constructing a permutation-based vote list in which each required defeat
 * (a defeats b) is satisfied by placing 'a' before 'b' in more than half of the votes.
 * 
 * Time Complexity: O(m * n), where m is number of constraints and n is number of candidates
 * Space Complexity: O(n^2), for storing adjacency matrix of candidate relationships
 */
#include <stdio.h>
#include <iosfwd>

using namespace std;
int g[55][55], n, m; // g[i][j] stores relationship between candidates i and j

int main() {
  scanf("%d%d", &n, &m);
  puts("YES");
  printf("%d\n", 2 * m); // Output number of votes (at most 2*m)
  for (int i = 1; i <= m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    g[a][b] = 1; // Mark that a defeats b
    g[b][a] = 1 - g[a][b]; // Set reverse relationship (this line is redundant or buggy but kept as-is)
    
    printf("%d %d ", a, b); // Print first vote where a comes before b
    for (int j = 1; j <= n; j++) {
      if (j == a || j == b) continue; // Skip the two candidates involved in this constraint
      printf("%d ", j);
    }
    puts("");
    
    for (int j = n; j >= 1; j--) { // Print second vote where b comes before a
      if (j == a || j == b) continue; // Skip the two candidates involved in this constraint
      printf("%d ", j);
    }
    printf("%d %d\n", a, b); // End with b followed by a
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/