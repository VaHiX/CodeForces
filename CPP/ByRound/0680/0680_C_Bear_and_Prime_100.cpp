// Problem: CF 680 C - Bear and Prime 100
// https://codeforces.com/contest/680/problem/C

/*
 * Problem: Bear and Prime 100
 * 
 * Purpose: Determine if a hidden integer in [2, 100] is prime or composite by querying divisors.
 * 
 * Approach:
 * - Precompute all primes up to 100 using sieve of Eratosthenes.
 * - Collect potential divisors to query: all primes and some composite squares (4, 9, 25, 49).
 * - Query these divisors up to 20 times to count how many divide the hidden number.
 * - If more than one divisor is found, the number is composite; otherwise, it's prime.
 * 
 * Time Complexity: O(N log log N) for sieve + O(1) for queries = O(N log log N) where N = 100
 * Space Complexity: O(N) for storing prime flags and divisor list where N = 100
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100005
#define mod 1000000007
using namespace std;

int prime[110];

// Function to generate all primes up to 100 using sieve of Eratosthenes
void sieve() {
  int i, j, k;
  memset(prime, -1, sizeof(prime)); // Initialize all to -1 (unknown)
  prime[0] = 0; // 0 is not prime
  prime[1] = 0; // 1 is not prime
  prime[2] = 1; // 2 is prime
  
  // Mark all even numbers > 2 as not prime
  for (i = 4; i < 110; i += 2)
    prime[i] = 0;
    
  // Check odd numbers starting from 3
  for (i = 3; i < 110; i += 2) {
    if (prime[i] == -1) { // If not yet marked
      prime[i] = 1; // Mark as prime
      k = 2;
      j = i * k; // Start with i*2
      while (j < 110) {
        prime[j] = 0; // Mark multiples as not prime
        k++;
        j = i * k;
      }
    }
  }
}

int main() {
  int i, j, k;
  int n, m;
  string s;
  
  // Generate primes up to 100
  sieve();
  
  // Store potential divisors to query
  vector<int> v;
  map<int, bool> mp;
  
  // Add all primes to our query list
  for (i = 2; i <= 100; i++) {
    if (prime[i])
      v.push_back(i);
    // Also add specific composite squares that are useful for determining primality
    if (i == 4 || i == 9 || i == 25 || i == 49)
      v.push_back(i);
  }
  
  int cnt = 0; // Count how many queries returned "yes"
  
  // Ask up to 20 queries
  for (i = 0; i < 20; i++) {
    cout << v[i] << endl; // Ask for the next divisor
    fflush(stdout); // Flush output buffer
    cin >> s; // Read response
    if (s == "yes") // If that number divides the hidden number
      cnt++;
  }
  
  // Output result
  if (cnt > 1)
    cout << "composite" << endl; // More than one divisor implies composite
  else
    cout << "prime" << endl; // Only one divisor implies prime
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/