// Problem: CF 757 C - Felicity is Coming!
// https://codeforces.com/contest/757/problem/C

/*
 * Problem: Felicity is Coming!
 * Purpose: Count the number of valid evolution plans such that the number of Pokemons
 *          of each type remains the same in each gym after evolution.
 *
 * Algorithm:
 * - For each Pokemon type, collect the list of gyms where it appears.
 * - Sort these lists lexicographically.
 * - Two types are considered equivalent if their lists of gyms are identical.
 * - For each group of equivalent types, the number of permutations is the factorial of the group size.
 * - Multiply all such factorials to get the total number of valid evolution plans.
 *
 * Time Complexity: O(m log m + total_pokemons), where m is number of types and total_pokemons is sum of all g_i.
 * Space Complexity: O(m * average_gym_size), for storing lists of gyms per type.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  const ll MOD = 1000000007;
  long n, m;
  scanf("%ld %ld", &n, &m);
  
  // a[i] stores the list of gyms where type i+1 appears
  std::vector<std::vector<long>> a(m);
  
  // Read input and populate the gym lists for each type
  for (long p = 0; p < n; p++) {
    long g;
    scanf("%ld", &g);
    while (g--) {
      long x;
      scanf("%ld", &x);
      a[x - 1].push_back(p);  // Store gym index (0-based)
    }
  }
  
  // Sort the lists of gyms for each type
  sort(a.begin(), a.end());
  
  // Count groups of types with same gym list
  long t(1);      // Length of current group
  ll cnt(1);      // Result: number of valid evolution plans
  
  for (long p = 1; p < m; p++) {
    if (a[p] == a[p - 1]) {
      // Same gym list as previous type: increment group size
      ++t;
      cnt *= t;
      cnt %= MOD;
    } else {
      // New gym list: reset group size
      t = 1;
    }
  }
  
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/