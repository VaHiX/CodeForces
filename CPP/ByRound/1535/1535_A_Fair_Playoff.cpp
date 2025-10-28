// Problem: CF 1535 A - Fair Playoff
// https://codeforces.com/contest/1535/problem/A

/*
Fair Playoff

Algorithm:
- For each test case, we have 4 players with different skill levels.
- In the first round, players 1 vs 2 and 3 vs 4 compete.
- Winners of these two matches face off in the final.
- The tournament is "fair" if the two strongest players meet in the finals.
- We sort the players by skill in descending order.
- Then, we determine which two players advance to the finals:
  - The strongest two players (after sorting) are the winners of their respective first round matches.
  - Player with highest skill is at index 0, second highest at index 1.
  - Indices of the winners in the finals: a[0].second / 2 and a[1].second / 2.
  - If they are equal (i.e., both came from same pair), then tournament is unfair.

Time Complexity: O(1) per test case (sorting a fixed-size array of 4 elements)
Space Complexity: O(1) (fixed size vector of 4 pairs)

*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<std::pair<long, long>> a(4); // Store skill and original index
    for (long p = 0; p < 4; p++) {
      scanf("%ld", &a[p].first);
      a[p].second = p; // Keep track of original position
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order by skill
    long x(a[0].second), y(a[1].second); // Get original indices of top two players
    x /= 2; // Determine which pair they came from (0 or 1)
    y /= 2; // Determine which pair they came from (0 or 1)
    puts(x == y ? "NO" : "YES"); // If same pair, finals have two players from same match -> unfair
  }
}


// https://github.com/VaHiX/codeForces/