// Problem: CF 2065 G - Skibidus and Capping
// https://codeforces.com/contest/2065/problem/G

/*
G. Skibidus and Capping
Algorithms/Techniques: Sieve of Eratosthenes, Semi-prime detection, Prefix counting, Modular arithmetic
Time Complexity: O(n * log(n) + MAXN * log(log(MAXN))) where n is the size of array and MAXN = 200000
Space Complexity: O(MAXN) where MAXN = 200000

The solution uses a precomputed sieve to identify primes and semi-primes.
For each element in the input array, we calculate how many valid pairs (i,j) with i <= j have lcm(a[i], a[j]) as a semi-prime.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
int n, a[200002], c[200002], t[200002], p[200002], q[200002], s[200002];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), t[i] = s[i] = 0; // Initialize arrays
  ll ans = 0;
  int tmp = 0;
  for (int i = 1; i <= n; i++) {
    if (c[a[i]] == 2) { // If a[i] is a semi-prime
      // Add contribution of previous occurrences and adjust for duplicates
      ans += t[p[a[i]]] + t[q[a[i]]] + t[a[i]] + 1;
      s[p[a[i]]]++; // Increment count for prime p[a[i]]
      s[q[a[i]]]++; // Increment count for prime q[a[i]]
      if (q[a[i]] == p[a[i]]) // If p and q are same (e.g. 9 = 3*3)
        s[p[a[i]]]--, ans -= t[q[a[i]]]; // Adjust for overcounting
    } else if (c[a[i]] == 0) // If a[i] is a prime (not yet seen)
      ans += tmp - t[a[i]] + s[a[i]], tmp++; // Add pairs based on previous counts
    t[a[i]]++; // Increment count of element a[i]
  }
  printf("%lld\n", ans);
}

int main() {
  // Preprocessing primes using sieve of Eratosthenes
  for (int i = 2; i <= 200000; i++)
    if (!c[i])
      for (int j = i + i; j <= 200000; j += i)
        c[j] = 1;
  // Preprocessing semi-primes
  for (int i = 2; i <= 200000; i++)
    if (c[i] == 0) // If i is prime
      for (int j = 2; i * j <= 200000; j++)
        if (c[j] == 0) { // If j is also prime, then i*j is a semi-prime
          c[i * j] = 2; // Mark as semi-prime
          p[i * j] = i; // Store first prime factor
          q[i * j] = j; // Store second prime factor
        }
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/