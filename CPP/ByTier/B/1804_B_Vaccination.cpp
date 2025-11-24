// Problem: CF 1804 B - Vaccination
// https://codeforces.com/contest/1804/problem/B

/*
B. Vaccination
Algorithm: Greedy approach with interval scheduling
Time Complexity: O(n) per test case, where n is the number of patients
Space Complexity: O(1)

This problem involves minimizing the number of vaccine packs needed to vaccinate all patients,
given constraints on:
- Each pack has k doses
- Each dose lasts for d time units outside fridge
- Each patient can wait w time units from their arrival
- Patients must be vaccinated within [t_i, t_i + w] time range
- Vaccines opened at time x are usable until time x + d

Approach:
We use a greedy strategy to assign patients to vaccine packs. For each patient, we either:
1. Start a new pack (if no existing pack can cover this patient)
2. Use an existing pack if possible (based on timing and remaining capacity)

The key insight is that we can delay assignment of a patient to a pack until the latest possible moment
within their allowed window [t_i, t_i + w] while still ensuring coverage within pack's lifetime.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, d, w;
    scanf("%ld %ld %ld %ld", &n, &k, &d, &w);
    long cnt(0), rem(0), exp(-1); // cnt: number of packs used, rem: remaining doses in current pack, exp: expiration time of current pack
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (rem <= 0 || exp < x) { // if no pack is active or current pack expires before patient arrives
        ++cnt;                   // open a new pack
        rem = k - 1;             // one dose used, k-1 remaining
        exp = x + w + d;         // expiration time of this pack
      } else {
        --rem; // use one dose from current pack
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/