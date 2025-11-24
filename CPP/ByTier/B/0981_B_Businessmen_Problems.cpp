// Problem: CF 981 B - Businessmen Problems
// https://codeforces.com/contest/981/problem/B

/*
Purpose: 
This code solves the problem of maximizing the total income from two competing companies (ChemForces and TopChemist) 
that discover chemical elements. Each element can only be used by one company, and the goal is to assign elements to 
maximize the sum of incomes.

Approach:
- We use a map to store elements and their maximum income if they appear in both companies.
- For each element, we keep only the maximum income (either from ChemForces or TopChemist).
- The final answer is the sum of all maximum incomes for unique elements.

Algorithms/Techniques:
- Map-based approach for handling duplicate elements
- Greedy selection of maximum income per element

Time Complexity: O(n log n + m log m)
Space Complexity: O(n + m)
*/

#include <cstdio>
#include <map>
#include <utility>

typedef long long ll;
int main() {
  std::map<ll, ll> r; // Map to store element index and maximum income
  ll n;
  scanf("%lld", &n);
  while (n--) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    if (r.count(x)) {
      // If element already exists, keep the maximum income
      r[x] = (r[x] > y) ? r[x] : y;
    } else {
      r[x] = y; // Add new element with its income
    }
  }
  ll m;
  scanf("%lld", &m);
  while (m--) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    if (r.count(x)) {
      // If element already exists, keep the maximum income
      r[x] = (r[x] > y) ? r[x] : y;
    } else {
      r[x] = y; // Add new element with its income
    }
  }
  ll total(0);
  // Sum all maximum incomes for unique elements
  for (std::map<ll, ll>::iterator it = r.begin(); it != r.end(); it++) {
    total += it->second;
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/