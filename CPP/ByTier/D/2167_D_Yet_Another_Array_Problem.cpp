// Problem: CF 2167 D - Yet Another Array Problem
// https://codeforces.com/contest/2167/problem/D

/*
 * Problem: D. Yet Another Array Problem
 * 
 * Purpose: Find the smallest integer x (2 <= x <= 10^18) such that there exists
 * an index i where gcd(a[i], x) = 1.
 * 
 * Approach:
 * - If the GCD of all elements in the array is 1, then we can choose x = 2,
 *   since gcd(2, a[i]) = 1 for any odd a[i], and for even a[i], gcd(2, a[i]) > 1
 *   only when a[i] is even. If all elements are even, the overall GCD would not be 1.
 * - If the GCD of the array is greater than 1, then there's a common prime divisor p.
 *   Then we look for the smallest prime from a predefined list that does not divide g.
 * 
 * Algorithm:
 *   1. Compute the GCD of all elements in the array.
 *   2. If GCD is 1, return 2.
 *   3. Else, iterate through a list of small primes and find the smallest one
 *      which does not divide the GCD. That prime will be our answer.
 * 
 * Time Complexity: O(n * log(max(a[i])) + primesCount) ≈ O(n * log(10^18) + 26)
 * Space Complexity: O(1) - fixed size prime list, input stored in array of size up to 1e5.
 */
#include <iostream>

using namespace std;
using int64 = long long;

// Standard GCD implementation using Euclidean algorithm
long long gcd_ll(long long a, long long b) {
  while (b != 0) {
    long long temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  // Predefined list of small primes to check against the GCD
  long long primes[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
  int primesCount = 26;
  
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    long long a[100005];
    for (int i = 0; i < n; i++)
      cin >> a[i];
    
    // Compute the GCD of all elements
    long long g = a[0];
    for (int i = 1; i < n; i++)
      g = gcd_ll(g, a[i]);
    
    // If GCD is 1, we can always pick x = 2 (since gcd(2, odd number) = 1)
    if (g == 1) {
      cout << 2 << "\n";
      continue;
    }
    
    long long ans = -1;
    // Check each prime to find the smallest one that doesn't divide g
    for (int i = 0; i < primesCount; i++) {
      if (g % primes[i] != 0) {
        ans = primes[i];
        break;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/