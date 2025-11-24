// Problem: CF 1203 C - Common Divisors
// https://codeforces.com/contest/1203/problem/C

/*
C. Common Divisors
Algorithm: Find the GCD of all elements in the array. Then count the number of divisors of this GCD.
Techniques: 
  - Euclidean algorithm for GCD computation (__gcd)
  - Prime factorization to count divisors
Time Complexity: O(n + sqrt(gcd)), where n is the size of input array and gcd is the GCD of all elements
Space Complexity: O(1)

Input:
  First line contains n (number of elements)
  Second line contains n integers (array elements)
Output:
  Number of common divisors of all elements in the array
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>

using namespace std;
int64_t n, i, x, g, r = 1; // g stores GCD of all numbers, r stores result (number of divisors)
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  for (cin >> n; n--;) // Read all numbers and compute their GCD
    cin >> x, g = __gcd(g, x); // Update GCD with each new number
  for (i = 2, x = 0; i * i <= g; i++) { // Iterate through potential prime factors up to sqrt(g)
    for (; g % i == 0;) // While current number divides g
      g /= i, x++; // Divide g by i and increment exponent count
    r *= x + 1; // Multiply result by (exponent + 1) - this is from divisor counting formula
    x = 0; // Reset exponent counter for next prime
  }
  g > 1 ? r *= 2 : 0; // If remaining g > 1, it's a prime factor with exponent 1, so multiply by (1+1)=2
  cout << r; // Output number of divisors
}


// https://github.com/VaHiX/codeForces/