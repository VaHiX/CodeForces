// Problem: CF 776 B - Sherlock and his girlfriend
// https://codeforces.com/contest/776/problem/B

/*
Code Purpose:
This code solves the problem of coloring jewelry pieces such that no two pieces with prices where one is a prime divisor of the other have the same color.
It uses a sieve of Eratosthenes to precompute prime numbers and then assigns colors based on whether each price is prime or not.

Algorithm:
1. Use sieve of Eratosthenes to find all prime numbers up to n+1.
2. Count how many primes and non-primes exist in the range [2, n+1].
3. If there are no non-primes, only one color is needed.
4. Otherwise, assign color 1 to primes and color 2 to non-primes.

Time Complexity: O(n log log n) due to the sieve of Eratosthenes algorithm.
Space Complexity: O(n) for the boolean array to store prime status.
*/

#include <string.h>
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
bool prime[100005]; // Boolean array to store prime status of numbers
void sieve() {
  memset(prime, 1, sizeof(prime)); // Initialize all entries as true (prime)
  prime[0] = prime[1] = 0; // 0 and 1 are not primes
  for (int i = 4; i <= 100005; i += 2) // Mark all even numbers except 2 as not prime
    prime[i] = 0;
  for (int i = 3; i <= 100005; i += 2) { // Check odd numbers starting from 3
    if (prime[i]) { // If i is still marked as prime
      for (int j = i * 2; j <= 100005; j += i) { // Mark multiples of i as not prime
        prime[j] = 0;
      }
    }
  }
}
using namespace std;
int main() {
  ll i, j, k;
  ll n;
  cin >> n;
  sieve(); // Precompute primes up to n+1
  ll pr = 0, npr = 0; // Count of primes and non-primes
  for (i = 2; i <= n + 1; i++) { // Loop through prices from 2 to n+1
    if (prime[i])
      pr++; // Increment prime count
    else
      npr++; // Increment non-prime count
  }
  if (npr == 0) // If there are no non-primes
    cout << "1" << endl; // Only one color needed
  else
    cout << "2" << endl; // Otherwise, two colors needed
  for (i = 2; i <= n + 1; i++) { // Output the colors for each piece
    if (prime[i])
      cout << "1 "; // Assign color 1 to primes
    else
      cout << "2 "; // Assign color 2 to non-primes
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/