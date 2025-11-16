// Problem: CF 854 A - Fraction
// https://codeforces.com/contest/854/problem/A

/*
Algorithm/Techniques: 
    - Brute-force search for the numerator 'a' such that:
        - a < n - a (i.e. fraction is proper)
        - gcd(a, n - a) == 1 (i.e. fraction is irreducible)
    - Start from p = 1 and go up to p < (n - p), checking the GCD condition.
    - The largest valid p will give us the maximum proper irreducible fraction.

Time Complexity: O(n * log(n)) where n <= 1000. For each p, we compute GCD which is O(log(n)).
Space Complexity: O(1) - only using a constant amount of extra space.
*/

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long n;
  scanf("%ld", &n);
  long a(0);
  // Loop through all possible numerators p where p < n - p
  for (long p = 1; p < (n - p); p++) {
    // Check if p and (n - p) are coprime (irreducible fraction)
    if (gcd(p, n - p) == 1) {
      a = p; // Store the valid numerator
    }
  }
  printf("%ld %ld\n", a, n - a);
  return 0;
}


// https://github.com/VaHiX/CodeForces/