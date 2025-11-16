// Problem: CF 1474 B - Different Divisors
// https://codeforces.com/contest/1474/problem/B

/*
B. Different Divisors
Purpose: Given a positive integer d, find the smallest positive integer a such that:
- a has at least 4 divisors,
- the difference between any two divisors of a is at least d.

Algorithm:
1. For each test case:
   - Start with `first = findPrime(d + 1)` — finds the smallest prime > d.
   - Then, `second = findPrime(first + d)` — finds the next prime such that the difference from first is at least d.
   - Return the product of these two primes: first * second.

Time Complexity: O(sqrt(max_val) * log(max_val)) where max_val is approximately 1e7 due to recursion in findPrime.
Space Complexity: O(log(max_val)) due to recursion stack depth.

Note: This approach exploits the fact that for minimal a with 4 divisors satisfying difference constraint,
the optimal solution often involves two primes p and q such that q >= p + d, and a = p * q.
*/

#include <cmath>
#include <iostream>

using namespace std;
typedef long long ll;
bool flag = false;

// Function to find the next prime number >= x
int findPrime(int x) {
  for (int i = 2; i <= sqrt(x); i++) {        // Check divisibility up to sqrt(x)
    if (x % i == 0) {                         // If x is not prime
      x++;                                    // Increment and try again recursively
      x = findPrime(x);                       // Recursive call to find next prime
      return x;
    }
  }
  return x;                                   // x is prime, return it
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int d;
    cin >> d;
    int first, second;
    first = findPrime(d + 1);                 // First prime after d
    second = findPrime(first + d);            // Second prime at least d distance away from first
    cout << first * second << "\n";           // Output product of two primes
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/