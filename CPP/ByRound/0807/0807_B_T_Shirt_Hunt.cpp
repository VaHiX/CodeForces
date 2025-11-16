// Problem: CF 807 B - T-Shirt Hunt
// https://codeforces.com/contest/807/problem/B

/*
Algorithm: T-Shirt Hunt
Purpose: Determine the minimum number of successful hacks needed to both win the current round and secure a T-shirt based on a pseudocode-generated selection process.

Approach:
- The pseudocode generates 25 distinct place numbers for T-shirt winners using a deterministic function from a score 's'.
- We aim to find the smallest score 'res' >= y such that:
    1. It's sufficient to win the current round (res >= y).
    2. The place 'u' (your Codecraft-17 place) is among the 25 generated places.
- Since each successful hack gives +100 points and each unsuccessful gives -50, we iterate over scores of the form res = x + k*50 where k >= 0.
- For each such score, check if 'u' is in the generated list via the 'lucky' function.
- If we find such a score, compute how many successful hacks are needed.

Time Complexity: O(1) average case due to limited range (at most 100 checks for the loop in lucky function and a bounded number of res values to check).
Space Complexity: O(1) - only using constant extra space.

*/
#include <cstdio>
bool lucky(int s, int u) {
  int w = (s / 50) % 475;  // Initialize w from the initial score s
  for (int p = 0; p < 25; p++) {
    w = (w * 96 + 42) % 475;  // Update w using the deterministic formula
    if (w + 26 == u) {        // Check if current place matches u
      return true;
    }
  }
  return false;  // u not found in the generated list
}
int main() {
  int u, x, y;
  scanf("%d %d %d", &u, &x, &y);
  int res = (x % 50);  // Start res to be at least y, adjusting for starting remainder
  while (res < y || !lucky(res, u)) {  // Loop until score is valid and u is in the T-shirt list
    res += 50;
  }
  // Calculate number of successful hacks required
  printf("%d\n", (res <= x) ? 0 : (res - x + 99) / 100);
  return 0;
}


// https://github.com/VaHiX/CodeForces/