// Problem: CF 859 A - Declined Finalists
// https://codeforces.com/contest/859/problem/A

/*
Purpose: This program determines the minimum number of contestants who declined invitations to the final round.
         It uses the known ranks of the finalists to calculate how many contestants with higher ranks must have 
         declined for the given list to be valid.

Algorithms/Techniques: 
    - Single pass through the input ranks to find the maximum rank.
    - Simple arithmetic to compute the number of declined contestants.

Time Complexity: O(K), where K is the number of finalists whose ranks are known.
Space Complexity: O(1), as we only use a constant amount of extra space.

*/
#include <cstdio>
int main() {
  const int F = 25;  // Number of finalists invited
  long k;
  scanf("%ld", &k);
  long maxRank(0);   // Track the highest rank among known finalists
  for (long p = 0; p < k; p++) {
    long x;
    scanf("%ld", &x);
    maxRank = (maxRank > x) ? maxRank : x;  // Update maxRank with the larger of the two
  }
  // If the maximum rank is greater than F (25), then (maxRank - F) contestants must have declined
  printf("%ld\n", (maxRank > F) ? (maxRank - F) : 0);
  return 0;
}


// https://github.com/VaHiX/CodeForces/