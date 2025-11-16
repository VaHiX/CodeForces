// Problem: CF 703 B - Mishka and trip
// https://codeforces.com/contest/703/problem/B

/*
 * Problem: Mishka and Trip
 * 
 * Purpose:
 *   Calculate the total cost of all roads in a country with n cities and k capital cities.
 *   Each road connects two cities, and its cost is the product of the beauty values of the two cities.
 *   The country has a cyclic road structure between all cities, plus direct roads from each capital city to every other city.
 * 
 * Algorithms/Techniques:
 *   - Preprocessing: Compute sum of all city beauty values
 *   - For each capital city, subtract its beauty value from the total sum and add to answer the product of remaining sum and capital's beauty value
 *   - For each non-capital adjacent pair in the cycle, compute their product and add to the answer
 * 
 * Time Complexity: O(n + k)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
#define ll long long int
#define sc(a) scanf("%lld", &a)
#define f0(n) for (ll i = 0; i < n; i++)
#define f1(n) for (ll i = 1; i <= n; i++)
ll c[100005];  // Array to store beauty values of cities
ll f[100005];  // Array to mark if a city is a capital city (1 if capital, 0 otherwise)
int main() {
  ll n, k, sm = 0, a, ans = 0;
  sc(n);  // Read number of cities
  sc(k);  // Read number of capital cities
  f1(n) {
    sc(c[i]);  // Read beauty value of city i
    sm = sm + c[i];  // Add to total sum of beauty values
  }
  f1(k) {
    sc(a);  // Read index of capital city
    f[a] = 1;  // Mark city a as capital
    sm = sm - c[a];  // Subtract its beauty value from total sum
    ans = ans + (sm * c[a]);  // Add the product of remaining sum and this capital's beauty to answer
  }
  f1(n) {
    if (f[i] == 0 && f[(i % n) + 1] == 0)  // If both city i and next city (cycling) are not capitals
      ans = ans + (c[i] * c[(i % n) + 1]);  // Add the product of beauty values of adjacent non-capital cities
  }
  printf("%lld\n", ans);  // Print the total cost
}


// https://github.com/VaHiX/CodeForces/