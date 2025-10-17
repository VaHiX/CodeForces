// Problem: CF 1749 B - Death's Blessing
// https://codeforces.com/contest/1749/problem/B

/*
B. Death's Blessing

Algorithm:
- For each monster, we calculate the total time to kill it and the additional health boost it gives to neighbors.
- The idea is to simulate the process of killing monsters in an optimal order to minimize total time.
- We can observe that when we kill a monster, it affects its adjacent neighbors with spell strength.
- The minimum time is computed by summing up all individual monster healths and subtracting the maximum spell strength that was not applied, because one of them would have been saved from being affected.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long res(0); // Total time to kill all monsters
    long x(0), mx(0); // x: current monster health, mx: max spell strength
    
    // Read health of all monsters and add to total time
    for (long p = 0; p < n; p++) {
      scanf("%ld", &x);
      res += x;
    }
    
    // Read spell strengths and compute the maximum spell that will be "saved"
    // from being applied, since one monster's spell isn't affecting anyone after its death
    for (long p = 0; p < n; p++) {
      scanf("%ld", &x);
      res += x;             // Add the spell strength (this contributes to time in some way)
      mx = (mx > x) ? mx : x; // Keep track of maximum spell strength
    }
    
    res -= mx; // Subtract maximum spell, because it isn't applied to anyone after death
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/