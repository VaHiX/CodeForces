// Problem: CF 492 D - Vanya and Computer Game
// https://codeforces.com/contest/492/problem/D

/*
Purpose: Determine which player (Vanya or Vova) makes the last hit on each monster.
         Each player attacks at fixed frequencies x and y hits per second.
         The time to raise weapon is 1/x and 1/y seconds respectively.
         For each monster with 'hits' required, compute when each player would make their next hit
         and determine who makes the final hit.

Algorithms/Techniques:
- Mathematical calculation to simulate hit timing based on attack frequencies
- Use of modular arithmetic and integer division to compute hit positions

Time Complexity: O(n), where n is the number of monsters
Space Complexity: O(1), only using a constant amount of extra space
*/

#include <cstdio>
int main() {
  long long n, x, y;
  scanf("%lld %lld %lld\n", &n, &x, &y);
  while (n--) {
    long long hits;
    scanf("%lld\n", &hits);
    // Calculate hit positions for Vanya and Vova based on their attack frequencies
    const long long hx = (hits + 1) * x / (x + y) - hits * x / (x + y);
    const long long hy = (hits + 1) * y / (x + y) - hits * y / (x + y);
    // Compare hit positions to determine who made the last hit
    puts((hx == hy) ? "Both" : (hx > 0 ? "Vanya" : "Vova"));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/