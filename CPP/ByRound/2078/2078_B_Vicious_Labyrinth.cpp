// Problem: CF 2078 B - Vicious Labyrinth
// https://codeforces.com/contest/2078/problem/B

/*
B. Vicious Labyrinth

Purpose:
This code solves a problem where we need to configure teleporters in a labyrinth such that 
every person moves to minimize the total distance from the exit after exactly k teleportations.

Approach:
- For each cell i, initially it is at distance n - i from the exit.
- The idea is to use a cyclic pattern of teleportation to reduce the overall distance sum.
- When k is odd, we try to send people closer to the exit in a way that balances movement.
- When k is even, we alternate between two configurations to ensure minimal total distance.

Algorithm:
1. For each test case, read n and k.
2. Reduce k modulo 2 because only parity affects the result.
3. For all cells except the last two (n-1 and n): print value `n - !k`.
4. For the last two cells (n-1 and n), print `n` followed by `n-1`.

Time Complexity: O(n) per test case, as we iterate through cells once.
Space Complexity: O(1) additional space, not counting input/output storage.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    k %= 2;  // Only parity matters for the result
    for (long p = 1; p <= n - 2; p++) {
      printf("%ld ", n - !k);  // Print teleport destination based on parity of k
    }
    printf("%ld %ld\n", n, n - 1);  // Last two cells handled separately
  }
}


// https://github.com/VaHiX/codeForces/