// Problem: CF 1836 B - Astrophysicists
// https://codeforces.com/contest/1836/problem/B

/*
B. Astrophysicists

Problem Description:
We need to distribute k gold coins among n astrophysicists such that the total value in silver coins is k * g.
Each gold coin equals g silver coins. When distributing, rounding is applied: 
- If a person gets x silver coins, r = x % g
  - If r >= ceil(g / 2), they get x + (g - r) silver coins (rounding up)
  - Otherwise, they get x - r silver coins (rounding down)
Goal: Maximize the number of saved silver coins due to rounding.

Algorithm:
- For a fixed distribution, compute how much is paid and how much is saved.
- The optimal strategy involves distributing bonuses such that the total saved due to rounding is maximized.
- First, calculate a baseline where each person gets (k * g) / n silver coins.
- Then adjust by considering rounding behavior.

Time Complexity: O(1)
Space Complexity: O(1)

Approach:
We model the distribution assuming uniform allocation with adjustment for rounding.
By analyzing the rounding process, we derive how to distribute bonuses to minimize extra cost due to rounding.
The key insight is to calculate first and last segments of bonus distribution based on g and k,
and then compute how much can be saved by optimizing rounding.

*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k, g;
    scanf("%lld %lld %lld", &n, &k, &g);
    
    // Calculate base value for first (n-1) people
    ll first = (n - 1) * ((g - 1) / 2);
    
    // Calculate the remaining value for last person
    ll last = k * g - first;
    
    // If last is negative, set it to 0 (no bonus)
    if (last < 0) {
      last = 0;
    } else {
      // Add g / 2 to account for rounding up (if r >= ceil(g/2))
      last += g / 2;
    }
    
    // Calculate how many coins can be saved due to rounding
    ll saved = (k - (last / g)) * g;
    
    printf("%lld\n", saved);
  }
}


// https://github.com/VaHiX/codeForces/