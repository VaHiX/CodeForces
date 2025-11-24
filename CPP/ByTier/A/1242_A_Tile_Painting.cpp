// Problem: CF 1242 A - Tile Painting
// https://codeforces.com/contest/1242/problem/A


/*
Task: Find maximum number of different colors to paint a path of n tiles such that 
      tiles at positions i and j have same color if |j-i| is a divisor of n > 1.
      
Algorithms/Techniques: Prime factorization

Time Complexity: O(sqrt(n)) - We iterate up to sqrt(n) to find the smallest prime factor
Space Complexity: O(1) - Only using constant extra space

The problem reduces to finding the largest prime factor of n.
If n has a repeated prime factor, then we can only use 1 color.
Otherwise, the answer is n itself (when n is a prime or product of distinct primes).
*/

#include <iostream>

using namespace std;
long long n;
int main() {
  cin >> n;
  for (long long i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0)
        n /= i; // Reduce n by factor i
      if (n != 1)
        cout << 1; // If n has other prime factors, we can use only 1 color
      else
        cout << i; // Return the largest prime factor
      return 0;
    }
  }
  cout << n; // If no factor found, n is prime, so answer is n
}

// https://github.com/VaHiX/codeForces/