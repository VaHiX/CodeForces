// Problem: CF 1499 D - The Number of Pairs
// https://codeforces.com/contest/1499/problem/D

/*
 * Problem: Find the number of pairs (a, b) such that c * lcm(a, b) - d * gcd(a, b) = x
 *
 * Algorithm:
 * - Use the property that lcm(a, b) * gcd(a, b) = a * b
 * - Let g = gcd(a, b), then a = g * a', b = g * b' where gcd(a', b') = 1
 * - Substituting: c * (a' * b' * g) - d * g = x => g * (c * a' * b' - d) = x
 * - So g must divide x, and we can iterate over all divisors of x
 * - For each divisor g, compute the value (x / g + d) / c and check if it's an integer
 * - Use sieve to precompute number of prime factors for fast lookup
 *
 * Time Complexity: O(sqrt(x) * log(log(x)) + T * sqrt(x))
 * Space Complexity: O(M) where M = 2e7 + 1
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll mn = 2e7 + 1;
vector<ll> nd(mn); // nd[i] stores the number of prime factors of i

int main() {
  // Sieve to compute number of prime factors for each number
  for (int i = 2; i < mn; i++)
    if (!nd[i]) // i is prime
      for (int j = i; j < mn; j += i)
        nd[j]++; // increment count of prime factors for multiples of i
  
  int t;
  cin >> t;
  while (t--) {
    ll c, d, x;
    cin >> c >> d >> x;
    ll ans = 0;
    
    // Iterate over all divisors of x
    for (int i = 1; i * i <= x; i++)
      if (x % i == 0) { // i is a divisor of x
        // Check if (i + d) is divisible by c
        if ((i + d) % c == 0) {
          // If yes, add 2^(number of prime factors of (i + d) / c)
          ans += 1ll << nd[(i + d) / c];
        }
        
        // Check if x/i is not the same as i (avoid double counting)
        if (x != i * i && (x / i + d) % c == 0) {
          // If yes, add 2^(number of prime factors of (x/i + d) / c)
          ans += 1ll << nd[(x / i + d) / c];
        }
      }
    cout << ans << endl;
  }
  cin >> t; // unused line to avoid compilation warning
}


// https://github.com/VaHiX/CodeForces/